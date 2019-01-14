#include <linux/module.h>  
#include <linux/init.h>  
#include <linux/types.h>  
#include <linux/fs.h>  
#include <linux/mm.h>  
#include <linux/cdev.h>  
#include <linux/errno.h>  
#include <linux/sched.h>  
#include <asm/io.h>  
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/device.h>

#define simple_MAJOR 200

static unsigned char simple_inc  = 0;
static char demoBuffer[256];
dev_t devno;
static struct class *simpleclass;
static struct device *dev;

int simple_open(struct inode *inode,struct file *filp){
    if(simple_inc < 0) return -ERESTARTSYS;
    simple_inc++;
    return 0;
}

int simple_release(struct inode *inode,struct file *filp){
    simple_inc--;
    return 0;
}

ssize_t simple_read(struct file *filp, char __user *buf,size_t count,loff_t *fops){
    if(copy_to_user(buf,demoBuffer,count)){
        count = -EFAULT;
    }

    return count;
}

ssize_t simple_write(struct file *file,const char __user *buf,size_t count,loff_t *f_pos){  
    if (copy_from_user(demoBuffer + *f_pos,buf,count)){  
        count = -EFAULT;  
    }  
    return count;  
} 

static const struct file_operations simple_fops = {
    .owner = THIS_MODULE,
    .open = simple_open,
    .release = simple_release,
    .read = simple_read,
    .write = simple_write,
};

void simple_cleanup_module(void){
	if(dev != NULL) device_destroy(simpleclass,MKDEV(simple_MAJOR,0));
	if(simpleclass != NULL)class_destroy(simpleclass);
    unregister_chrdev(simple_MAJOR,"simple");
//	unregister_chrdev_region(devno,1);
    printk("simple_cleanip_module\n");
}

int simple_init_module(void){
    int ret;
/*
	ret = alloc_chrdev_region(&devno,0,1,"simple");
	if(ret < 0){
		printk("alloc devno error\n");
		return 0;
	}
    
    printk("devno is %d\n",devno);
	printk("devno is %d\n",MAJOR(devno));
	printk("devno minor is %d\n",MINOR(devno));
*/
    ret = register_chrdev(simple_MAJOR,"simple",&simple_fops);
	if(ret < 0){
		printk("unable register character device %d\n",simple_MAJOR);
		return -1;
	}
   
	simpleclass = class_create(THIS_MODULE,"simple");
	if(IS_ERR(simpleclass)){
		ret = PTR_ERR(simpleclass);
		printk("class create error%d\n",ret);
		goto fail_bad_class;
	}


	dev = device_create(simpleclass,NULL,MKDEV(simple_MAJOR,0),NULL,"simple");
	if(IS_ERR(simpleclass)){
		ret = PTR_ERR(dev);
		printk("device create error%d\n",ret);
		goto bad_device_create;
	}
	
	return 0;
bad_device_create:
	class_destroy(simpleclass);
fail_bad_class:
	unregister_chrdev(simple_MAJOR,"simple");
    return -1;
}

module_init(simple_init_module);
module_exit(simple_cleanup_module);

MODULE_LICENSE("GPL");

