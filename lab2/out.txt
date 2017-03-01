/*
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

*/
/*

asmlinkage long sys_qihao(char *dest, char *src)
{
	printk("Hello qihao\n");
	int fi = sys_open(src, O_RDONLY, 0);
	// if existed, delete
	int fo = sys_open(dest, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fi <= 0 || fo <= 0) {
		printk("open file error\n");
	}
	char buf[64];
	while (sys_read(fi, buf, 64) > 0) {
		sys_write(fo, buf, 64);
	}
	sys_close(fi);
	sys_close(fo);
	return 0;
}
*/

#include <syscall.h>
#include <stdlib.h>
int main() {
	syscall(666, "out.txt", "main.c");
	return 0;
}
