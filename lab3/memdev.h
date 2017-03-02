#ifndef _MEMDEV_H_
#define _MEMDEV_H_

#include <linux/module.h> 	/* init_module, cleanup_module() */
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/gfp.h>
#include <linux/init.h>
#include <linux/slab.h> /* kmalloc kfree */
#include <asm/uaccess.h>

#ifndef MEMDEV_MAJOR
#define MEMDEV_MAJOR 300   /*预设的mem的主设备号*/
#endif

#ifndef MEMDEV_NR_DEVS
#define MEMDEV_NR_DEVS 2    /*设备数*/
#endif

#ifndef MEMDEV_SIZE
#define MEMDEV_SIZE 4096
#endif




/*mem设备描述结构体*/
struct mem_dev                                     
{                                                        
  char *data;                      
  unsigned long size;       
};

#endif /* _MEMDEV_H_ */
