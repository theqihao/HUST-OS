


/* 1k */
#define MY_SIZE 1 << 10


typedef struct _Node Node;
struct _Node {
	long size;
	char *p;
};

static int num_major = 0;
/* designated initializer, C99  */
struct file_operations my_fops = {  
	.owner =    THIS_MODULE,  
	.read =     my_read,  
	.write =    my_write,  
	.open =     my_open,  
	.release =  my_release,  
	.ioctl =    my_ioctl, 
	.llseek =   my_llseek, 
}; 



int init_module(void) {
        // if success, return the major num of dev, else return a neg value
        int major = register_chrdev(0, "qihao", &fops);
        if (major < 0) {
                printf("register error\n");
        } else {
		num_major = major;
		printf("register success\n");
		printf("the num of major is : %d\n", major);
	}
	return major;	
}

void cleanup_module(void) {
	// if success, re = 0
	int re = unregister_chrdev(major, "qihao");
        if (re != 0) {
                printk("unregister error\n");
        } else {	
                printk("unregister success\n");
	}
}
