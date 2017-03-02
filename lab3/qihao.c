#include "qihao.h"

static qihao_major = QIHAO_MAJOR;
struct cdev cdev;
struct DEV *devp;

int my_open(struct inode *inode, struct file *filp) {
    struct DEV *dev;
    // get minor num 
    int num = MINOR(inode->i_rdev);
    if (num >= QIHAO_NR_DEVS) {
    	return -1;
    }
    dev = &devp[num];
    // default is null 
    filp->private_data = dev;
    return 0; 
}

int my_release(struct inode *inode, struct file *filp)
{
	filp->private_data = NULL;
	return 0;
}

static int my_read(struct file *filp, char __user *buffer, size_t length,loff_t *offset) {
	struct DEV *dev = filp->private_data;
	// if success, return 0
	if (copy_from_user(dev->data + *offset, buffer, length)) {
		return -1;
	} else {
		*offset += length;
		return length;
	}
}

static ssize_t my_write(struct file *filp, const char __user  *buffer, size_t length,loff_t *offset) {
	struct DEV *dev = filp->private_data;
	if (copy_to_user(buffer, (void *)(dev->data + *offset), length)) {
		return -1;
	} else {
		*offset += length;
		return length;
	}
}

static loff_t my_llseek(struct file *filp, loff_t offset, int whence)
{ 
    loff_t newpos;
    switch(whence) {
      case 0:
        newpos = offset;
        break;
      case 1:
        newpos = filp->f_pos + offset;
        break;
      case 2: 
        newpos = SIZE -1 + offset;
        break;
      default:
        return -EINVAL;
    }
    if ((newpos < 0) || (newpos > SIZE))
        return -EINVAL;
    filp->f_pos = newpos;
    return newpos;
}

static const struct file_operations my_fops =
{
	.owner = THIS_MODULE,
	.open = my_open,
	.release = my_release,
	.read = my_read,
	.write = my_write,
	.llseek = my_llseek,
};

static int my_init(void)
{
	int i;
	int ret;
	dev_t devno = MKDEV(qihao_major, 0);
	// static requst 
	if (qihao_major != 0) {
		ret = register_chrdev_region(devno, 2, "qihao");
	} else { 
		ret = alloc_chrdev_region(&devno, 0, 2, "qihao");
		qihao_major = MAJOR(devno);
	}
	if (ret < 0) return ret;
	
	// init cdev
	cdev_init(&cdev, &my_fops);
	cdev.owner = THIS_MODULE;
	cdev.ops = &my_fops;
	// count是添加的设备号的数量，具体的就是minor的数量。
	// the number of consecutive minor numbers corresponding to this device
	// register
	cdev_add(&cdev, MKDEV(qihao_major, 0), QIHAO_NR_DEVS);
	
	// mem
	// GFP_KERNEL是linux内存分配器的标志，标识着内存分配器将要采取的行为。
	devp = kmalloc(QIHAO_NR_DEVS * sizeof(struct DEV), GFP_KERNEL);
	if (!devp) {
		printk(KERN_INFO "get memory error");
		return EINVAL;
	} 
	memset(devp, 0, QIHAO_NR_DEVS * sizeof(struct DEV));
	for (i = 0; i < QIHAO_NR_DEVS; i++) {
		devp[i].size = SIZE;
		devp[i].data = kmalloc(SIZE, GFP_KERNEL);
		memset(devp[i].data, 0, devp[i].size);
	}
	return 0;
}

static void my_exit(void)
{
	cdev_del(&cdev); 
	kfree(devp);   
	kfree(devp->data); 
	unregister_chrdev_region(MKDEV(qihao_major, 0), 2);
}


/* 指定驱动程序所使用的许可证。常用的许可证有”GPL”/”GPL v2”/”Dual BSD/GPL”等，我们这里用的是GPL许可证。*/
MODULE_LICENSE("Dual MIT/GPL");
module_init(my_init);
module_exit(my_exit);
