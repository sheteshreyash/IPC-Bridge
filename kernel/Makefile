obj-m += telem0_driver.o

ccflags-y += -I$(src)/../shared

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
