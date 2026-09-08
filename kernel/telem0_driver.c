#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/kfifo.h>
#include <linux/wait.h>
#include <linux/poll.h>
#include <linux/workqueue.h>
#include <linux/gpio/consumer.h>
#include <linux/interrupt.h>

#include "../shared/telem0_protocol.h"

#define DEVICE_NAME "telem0"
#define FIFO_PACKET_CAPACITY 64

struct telem0_dev
{
    struct spi_device *spi;
    struct miscdevice miscdev;

    struct mutex lock;
    struct kfifo fifo;
    wait_queue_head_t readq;

    struct work_struct irq_work;

    struct gpio_desc *ready_gpiod;
    int irq;
};

static bool telem0_fifo_ready(struct telem0_dev *dev)
{
    return kfifo_len(&dev->fifo) >= sizeof(telem0_packet_t);
}

static irqreturn_t telem0_irq_handler(int irq, void *dev_id)
{
    struct telem0_dev *dev = dev_id;

    schedule_work(&dev->irq_work);
    return IRQ_HANDLED;
}

static void telem0_spi_work(struct work_struct *work)
{
    struct telem0_dev *dev = container_of(work, struct telem0_dev, irq_work);
    telem0_packet_t pkt;
    u8 tx_buf[sizeof(telem0_packet_t)] = {0};
    struct spi_message msg;
    struct spi_transfer xfer = {
        .tx_buf = tx_buf,
        .rx_buf = &pkt,
        .len = sizeof(pkt),
    };
    int ret;

    memset(&pkt, 0, sizeof(pkt));

    spi_message_init(&msg);
    spi_message_add_tail(&xfer, &msg);

    ret = spi_sync(dev->spi, &msg);
    if (ret)
    {
        dev_err(&dev->spi->dev, "spi_sync failed: %d\n", ret);
        return;
    }

    if (pkt.magic != TELEM0_PACKET_MAGIC)
    {
        dev_warn(&dev->spi->dev,
                 "invalid packet magic: 0x%08x\n",
                 pkt.magic);
        return;
    }

    mutex_lock(&dev->lock);

    if (kfifo_avail(&dev->fifo) >= sizeof(pkt))
    {
        kfifo_in(&dev->fifo, &pkt, sizeof(pkt));
        mutex_unlock(&dev->lock);
        wake_up_interruptible(&dev->readq);
        return;
    }

    mutex_unlock(&dev->lock);
    dev_warn(&dev->spi->dev, "fifo full, dropping packet\n");
}

static int telem0_open(struct inode *inode, struct file *file)
{
    struct telem0_dev *dev = container_of(file->private_data,
                                          struct telem0_dev,
                                          miscdev);
    file->private_data = dev;
    return 0;
}

static ssize_t telem0_read(struct file *file,
                           char __user *buf,
                           size_t len,
                           loff_t *ppos)
{
    struct telem0_dev *dev = file->private_data;
    telem0_packet_t pkt;
    int ret;

    if (len < sizeof(pkt))
        return -EINVAL;

    if (wait_event_interruptible(dev->readq, telem0_fifo_ready(dev)))
        return -ERESTARTSYS;

    mutex_lock(&dev->lock);

    if (!telem0_fifo_ready(dev))
    {
        mutex_unlock(&dev->lock);
        return -EAGAIN;
    }

    ret = kfifo_out(&dev->fifo, &pkt, sizeof(pkt));

    mutex_unlock(&dev->lock);

    if (copy_to_user(buf, &pkt, sizeof(pkt)))
        return -EFAULT;

    return sizeof(pkt);
}

static unsigned int telem0_poll(struct file *file, poll_table *wait)
{
    struct telem0_dev *dev = file->private_data;
    unsigned int mask = 0;

    poll_wait(file, &dev->readq, wait);

    if (telem0_fifo_ready(dev))
        mask |= POLLIN | POLLRDNORM;

    return mask;
}

static const struct file_operations telem0_fops = {
    .owner = THIS_MODULE,
    .open = telem0_open,
    .read = telem0_read,
    .poll = telem0_poll,
    .llseek = no_llseek,
};

static int telem0_probe(struct spi_device *spi)
{
    struct telem0_dev *dev;
    int ret;

    dev = devm_kzalloc(&spi->dev, sizeof(*dev), GFP_KERNEL);
    if (!dev)
        return -ENOMEM;

    dev->spi = spi;
    mutex_init(&dev->lock);
    init_waitqueue_head(&dev->readq);
    INIT_WORK(&dev->irq_work, telem0_spi_work);

    ret = kfifo_alloc(&dev->fifo,
                      FIFO_PACKET_CAPACITY * sizeof(telem0_packet_t),
                      GFP_KERNEL);
    if (ret)
        return ret;

    dev->miscdev.minor = MISC_DYNAMIC_MINOR;
    dev->miscdev.name = DEVICE_NAME;
    dev->miscdev.fops = &telem0_fops;

    spi_set_drvdata(spi, dev);

    ret = misc_register(&dev->miscdev);
    if (ret)
    {
        kfifo_free(&dev->fifo);
        return ret;
    }

    /*
     * Optional: ready-gpios from DT overlay.
     * On the Pi, this becomes the IRQ line from STM32 DATA_READY.
     */
    dev->ready_gpiod = devm_gpiod_get_optional(&spi->dev, "ready", GPIOD_IN);
    if (IS_ERR(dev->ready_gpiod))
    {
        ret = PTR_ERR(dev->ready_gpiod);
        goto err_misc;
    }

    if (dev->ready_gpiod)
    {
        dev->irq = gpiod_to_irq(dev->ready_gpiod);
        if (dev->irq < 0)
        {
            ret = dev->irq;
            goto err_misc;
        }

        ret = devm_request_irq(&spi->dev,
                               dev->irq,
                               telem0_irq_handler,
                               IRQF_TRIGGER_RISING,
                               DEVICE_NAME,
                               dev);
        if (ret)
            goto err_misc;
    }
    else
    {
        dev_warn(&spi->dev,
                 "ready-gpios not provided; IRQ path disabled for now\n");
    }

    dev_info(&spi->dev, "telem0 probed successfully\n");
    return 0;

err_misc:
    misc_deregister(&dev->miscdev);
    kfifo_free(&dev->fifo);
    return ret;
}

static int telem0_remove(struct spi_device *spi)
{
    struct telem0_dev *dev = spi_get_drvdata(spi);

    cancel_work_sync(&dev->irq_work);
    misc_deregister(&dev->miscdev);
    kfifo_free(&dev->fifo);

    dev_info(&spi->dev, "telem0 removed\n");
    return 0;
}

static const struct of_device_id telem0_of_match[] = {
    {.compatible = "ipc-bridge,telem0"},
    {}};
MODULE_DEVICE_TABLE(of, telem0_of_match);

static struct spi_driver telem0_driver = {
    .driver = {
        .name = "telem0",
        .of_match_table = telem0_of_match,
    },
    .probe = telem0_probe,
    .remove = telem0_remove,
};

module_spi_driver(telem0_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shreyash");
MODULE_DESCRIPTION("Sprint 3 telemetry SPI bridge with IRQ, SPI and kfifo");
