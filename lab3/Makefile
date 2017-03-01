ifneq ($(KERNELRELEASE), )
	#模块文件组成
	mymodule-objs := mychar.o
	#生成模块文件名
	obj-m := mychar.o
else
	PWD := $(shell pwd)
	KVER := $(shell uname -r)
	KDIR := /lib/modules/$(KVER)/build


all:
	$(MAKE) -C $(KDIR) M=$(PWD)
	
clean:
	rm -rf *.ko *.o *.mod.o *.mod.c *~ moudles.* Module.*
	
endif
