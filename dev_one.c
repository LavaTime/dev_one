//
// Created by LavaTime on 11/21/25.
//

#include "dev_one.h"
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("LavaTime");


const char one = 0x1;

static int dev_one_major;


static void __exit devOneExit(void)
{
    unregister_chrdev(dev_one_major, "dev_one");
    printk(KERN_INFO "dev_one: unregistered successfully\n");
}

static int devOneOpen(struct inode *inodep, struct file *filep)
{
    return 0;
}

static ssize_t devOneRead(struct file *flip, char __user *buffer, size_t len, loff_t *offset)
{
    if (copy_to_user(buffer, &one, 1)) {
        return -EFAULT;
    }

    return 1;
}

struct file_operations devOneFops = {
    owner: THIS_MODULE,
    open: devOneOpen,
    read: devOneRead
};

static int __init devOneInit(void)
{
    dev_one_major = register_chrdev(0, "dev_one", &devOneFops);
    if (dev_one_major < 0) {
        return -EFAULT;
    }
    printk(KERN_INFO "dev_one: major number %d\n", dev_one_major);
    return 0;
}

module_init(devOneInit);
module_exit(devOneExit);