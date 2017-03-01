#include <syscall.h>
int main() {
	syscall(666, "out.txt", "main.c");
	return 0;
}



/*

asmlinkage long sys_qihao(char *dest, char *src)
{
	printk("Hello qihao\n");
	int size = 1024;
	int fi = sys_open(src, O_RDONLY, 0);
	// if existed, delete 
	int fo = sys_open(dest, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fi <= 0 || fo <= 0) {
		printk("open file error\n");
	}
	// buf is __user, 这个指针应该指向空的内存，如果传递kernel空间的指针，会错 
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
*/
