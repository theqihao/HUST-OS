ifneq ($(KERNELRELEASE), )
	#模块文件组成
	mymodule-objs := qihao.o
	#生成模块文件名
	obj-m := qihao.o
else
	PWD := $(shell pwd)
	KVER := $(shell uname -r)
	KDIR := /lib/modules/$(KVER)/build


all:
	$(MAKE) -C $(KDIR) M=$(PWD)
	
	
test:
	gcc test.c -o qih
clean:
	rm -rf *.ko *.o *.mod.o *.mod.c *~ modules.* Module.*
	
endif
