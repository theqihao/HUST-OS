在编译内核模块时，
如有Makefile文件如下：
ifneq ($(KERNELRELEASE),)
param-objs := file1.o file2.o
obj-m := param.o
else
KDIR := /lib/modules/2.6.18-53.el5/buildall:
make -C $(KDIR) M=$(PWD) modulesclean:
rm -f *.ko *.o *.mod.o *.mod.c *.symversendif
KERNELRELEASE是在内核源码的顶层Makefile中定义的一个变量，在第一次读取执行此Makefile时，KERNELRELEASE没有被定义，所以make将读取执行else之后的内容，如果make的目标是clean，直接执行clean操作，然后结束。当make的目标为all时，-C $(KDIR)指明跳转到内核源码目录下读取那里的Makefile；M=$(PWD) 表明然后返回到当前目录继续读入、执行当前的Makefile。当从内核源码目录返回时，KERNELRELEASE已被定义，kbuild也被启动去解析kbuild语法的语句，make将继续读取else之前的内容。else之前的内容为kbuild语法的语句，指明模块源码中各文件的依赖关系，以及要生成的目标模块名。param-objs
:= file1.o file2.o 表示param.o由file1.o与file2.o 连接生成，obj-m := param.o表示编译连接后将生成param.o模块。


/* mychar */
模块加入：insmod mychar.ko
查看模块：lsmod | grep "mychar"
删除模块：rmmod mychar

1)cat /proc/devices看看有哪些编号已经被使用，我们选一个没有使用的XXX。
2)insmod memdev.ko
3)通过"mknod /dev/memdev0 c XXX 0"命令创建"/dev/memdev0"设备节点。
eg :
insmod mychar.ko
lsmod | grep "mychar"
mknod /dev/mychar c 666 0
ls /dev/ | grep "mychar"
cd /dev
chmod +777 mychar
rmmod mychar


cat /proc/devices  | grep "qih"
302 qihao

dmesg
