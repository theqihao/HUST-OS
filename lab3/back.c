#include <linux/module.h> 	/* init_module, cleanup_module() */
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/gfp.h>
#include <linux/init.h>
#include <linux/slab.h> /* kmalloc kfree */
#include <asm/uaccess.h>

/* 1k */
#define DEV_SIZE 1 << 10


typedef struct _Node Node;
struct _Node {
	long size;
	char *data;
};
Node *devp;
struct cdev cdev;
static int num_major = 0;




static int my_open(struct inode *inode, struct file *fp) {
	// default is null
	fp->private_data = devp;
	return 0;
}

static int my_read(struct file *filp, char __user *buffer,size_t length,loff_t *offset) {
	Node *dev = filp->private_data;
	// if success, return 0
	if (copy_from_user(dev->data + *offset, buffer, length)) {
		return -1;
	} else {
		*offset += length;
		return length;
	}
}

static ssize_t my_write(struct file *filp, const char __user  *buffer, size_t length,loff_t *offset) {
	Node *dev = filp->private_data;
	if (copy_to_user(buffer, (void *)(dev->data + *offset), length)) {
		return -1;
	} else {
		*offset += length;
		return length;
	}
}


/* designated initializer, C99  */
struct file_operations my_fops = {  
	.owner =    THIS_MODULE,  
	.read =     my_read,  
	.write =    my_write,  
	.open =     my_open,  
	/*.release =  my_release,  
	.ioctl =    my_ioctl, 
	.llseek =   my_llseek, */
}; 

int init_module(void) {
    // if success, return the major num of dev, else return a neg value
    int major = register_chrdev(0, "qihao", &my_fops);
    if (major < 0) {
            printk(KERN_INFO "register error\n");
	return major;
    } else {
		if (num_major ==0)
			num_major = major;
		printk(KERN_INFO "register success\n");
		printk(KERN_INFO "the num of major is : %d\n", major);
	}
	// init cdev
	cdev_init(&cdev, &my_fops);
	cdev.owner = THIS_MODULE;
	cdev.ops = &my_fops;
	// count是添加的设备号的数量，具体的就是minor的数量。
	// the number of consecutive minor numbers corresponding to this device
	// register
	cdev_add(&cdev, MKDEV(num_major, 0), 1);

	// mem
	// GFP_KERNEL是linux内存分配器的标志，标识着内存分配器将要采取的行为。
	devp = kmalloc(sizeof(struct _Node), GFP_KERNEL);
	if (!devp) {
		return -1;
		printk(KERN_INFO "get memory error");
	} 
	devp->size = DEV_SIZE;
	devp->data = kmalloc(DEV_SIZE, GFP_KERNEL);
	memset(devp->data, 0, devp->size);
	return 0;	
}

void cleanup_module(void) {
	cdev_del(&cdev);
	kfree(devp);
	kfree(devp->data);
	unregister_chrdev(num_major, "qihao");
}

/*
指定驱动程序所使用的许可证。常用的许可证有”GPL”/”GPL v2”/”Dual BSD/GPL”等，我们这里用的是GPL许可证。
*/
MODULE_LICENSE("Dual MIT/GPL");
//MOUDULE_LICENSE("GPL");
