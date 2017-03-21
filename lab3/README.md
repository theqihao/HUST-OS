# 文件说明
驱动程序：qihao.h qihao.c
测试程序：test.c

# 具体使用
生成模块：./add
测试：make test
执行:./qih
清理:make clean

# Makefile
KERNELRELEASE是在内核源码的顶层Makefile中定义的一个变量，在第一次读取执行此Makefile时，KERNELRELEASE没有被定义，
所以make将读取执行else之后的内容，如果make的目标是clean，直接执行clean操作，然后结束。
当make的目标为all时，-C $(KDIR)指明跳转到内核源码目录下读取那里的Makefile；M=$(PWD) 表明然后返回到当前目录继续读入、执行当前的Makefile。
当从内核源码目录返回时，KERNELRELEASE已被定义，make将继续读取else之前的内容。else之前的内容为kbuild语法的语句，指明模块源码中各文件的依赖关系，以及要生成的目标模块名。obj-m := param.o表示编译连接后将生成param.o模块。

# 操作
rmmod qihao
rm /dev/qihao*
make clean
make
insmod qihao.ko
mknod /dev/qihao0 c 333 0

# check
cat /proc/devices  | grep "qihao"

# debug
dmesg:查看内核输出
