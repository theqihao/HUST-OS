# 下载内核
* 'https://www.kernel.org/'
* apt-get install kernel-package build-essential libncurses5-dev fakeroot
* apt-get install libssl-dev build-essential
* xz -d linux-4.4.52.tar.xz
* tar -xvf linux-4.4.52.tar
* cp ./linux-4.4.52 /usr/src -rf
* cd /usr/src
# 编译内核
* 以root身份进入/usr/src/linux目录，重建内核
* make mrproper //清除之前编译信息，避免生成的文件不一致
* make oldconfig //配置内核与当前配置相同
	make config              基于文本的传统配置界面
	make menuconfig    基于文本的菜单形式，字符终端下使用
	make xconfig     基于图形窗口模式，Xwindow下使用
* make -j8          //编译内核
* make modules_install -j8//生成并安装模块
* make install -j8    //安装新的系统
* /*make bzImage；make modules；make modules_install; make install  */
	
# 添加代码
* linux-4.4.52/arch/x86/entry/syscalls/syscall_64.tbl
'''
666 common	qihao			sys_qihao
'''
* linux-4.4.52/include/linux/syscalls.h
- **
#ifndef sys_qihao
asmlinkage long sys_qihao(char *dest, char *src);
#endif
**
* linux-4.4.52/kernel/sys.c
- **
void copy(char* dest, char* src) {
    FILE* fi = fopen(src, "r");
    FILE* fo = fopen(dest, "w");
    if (fi == NULL) {
        printf("open %s failed!\n", src);
        return ;
    }
    if (fo == NULL) {
        printf("open %s failed!\n", dest);
        return ;
    }
    char c;
    // fread返回读取的字节数,如果返回0，说明读到了文件尾
    while (fread(&c, sizeof(c), 1, fi)) {
        fwrite(&c, sizeof(c), 1, fo);
    }
    fclose(fi);
    fclose(fo);
}
asmlinkage long sys_qihao(char *dest, char *src)
{
	printk("Hello qihao\n");
	int size = 1024;
	int fi = sys_open(src, O_RDONLY, 0);
	/* if existed, delete */
	int fo = sys_open(dest, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fi <= 0 || fo <= 0) {
		printk("open file error\n");
	}
	/* buf is __user, 这个指针应该指向空的内存，如果传递kernel空间的指针，会错 */
	mm_segment_t old_fs;
	old_fs = get_fs();
	set_fs(KERNEL_DS);
	char buf[size];
	int num;
	do {
		num = sys_read(fi, buf, size);
		sys_write(fo, buf, num);
	} while(num > 0);
	sys_close(fi);
	sys_close(fo);
	set_fs(old_fs);
	return 0;
}
**
重启选用新内核，同启动管理相关
update-grub
reboot

cat /proc/version



