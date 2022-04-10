obj-m += my_dummy_driver.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

load: all
	sudo insmod my_dummy_driver.ko
	sudo dmesg -c

unload:
	sudo rmmod my_dummy_driver.ko
	sudo dmesg -c
