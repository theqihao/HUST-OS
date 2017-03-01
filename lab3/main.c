#include <stdio.h>
#include <malloc.h>
#include "linux/kernel.h" 
#include "linux/module.h" 
/*处理版本问题CONFIG_MODVERSIONS */ 
#if CONFIG_MODVERSIONS==1 
#define MODVERSIONS 
#include "linux/version.h" 
#endif

int main() {
	printf("Hello world\n");
	struct file_operations fops;
	// 登记成功，返回设备的主设备号，否则，返回一个负值
	unsigned int major = register_chrdev(0, "qihao", &fops);
	if (major < 0) {
		printf("register error\n");
	}
	int re = unregister_chrdev(major, "qihao");	
	if (re != 0) {
		printf("unregister error\n");
	}
	return 0;
}
