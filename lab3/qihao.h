#ifndef _QIHAO_H_
#define _QIHAO_H_

#include <linux/module.h> 
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/gfp.h>
#include <linux/init.h>
//  kmalloc kfree 
#include <linux/slab.h> 
#include <asm/uaccess.h>

// major num of DEV 
#define QIHAO_MAJOR 333
// nums of dev  
#define QIHAO_NR_DEVS 2  
// buf size 
#define	SIZE 4096

struct DEV {                                                        
  char *data;                      
  unsigned long size;       
};

#endif

