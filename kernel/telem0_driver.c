#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/mutex.h>

#define DEVICE_NAME "telem0"

struct telem0_dev
{
    struct spi_device *spi;
    struct miscdevice miscdev;
    struct mutex lock;
};

static ssize_t telem0_read(struct file *file, char __user *buf, size_t len, loff_t *ppos)
{
    const char msg[] = "TELEM0_DRIVER_READY\n";
    return simple_read_from_buffer(buf, len, ppos, msg, sizeof(msg) - 1);
}

static int telem0_open(struct inode *inode, struct file *file)
{
    return 0;
}

static const struct file_operations telem0_fops = {
    .owner = THIS_MODULE,
    .open = telem0_open,
    .read = telem0_read,
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

    dev->miscdev.minor = MISC_DYNAMIC_MINOR;
    dev->miscdev.name = DEVICE_NAME;
    dev->miscdev.fops = &telem0_fops;

    spi_set_drvdata(spi, dev);

    ret = misc_register(&dev->miscdev);
    if (ret)
        return ret;

    dev_info(&spi->dev, "telem0: probed successfully\n");
    return 0;
}

static void telem0_remove(struct spi_device *spi)
{
    struct telem0_dev *dev = spi_get_drvdata(spi);

    if (dev)
        misc_deregister(&dev->miscdev);

    dev_info(&spi->dev, "telem0: removed\n");
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
MODULE_DESCRIPTION("Sprint 3 telemetry SPI bridge scaffold");
