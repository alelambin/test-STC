#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#define DEV_NAME "my_dummy_device"
#define BUFFER_SIZE (size_t) ((10) * PAGE_SIZE)

// global variables
static int dev_major = 0;
static int dev_minor = 0;
static struct class *class;
static struct device *device;

/**
 * Module opening
 * \param inode file identificator
 * \param file file struct
 * \return file descriptor
 */
static int module_open(struct inode *inode, struct file *file) {
    static int counter = 0;
    char *buffer = kmalloc(BUFFER_SIZE, GFP_KERNEL);
    file->private_data = buffer;
    counter++;
    
    printk(KERN_INFO "%s successfully opened\n", DEV_NAME);
    return 0;
}

/**
 * Module releasing
 * \param inode file identificator
 * \param file file struct
 * \return file descriptor
 */
static int module_release(struct inode *inode, struct file *file) {
    char *buffer = file->private_data;
    if (buffer)
        kfree(buffer);
    buffer = NULL;
    file->private_data = NULL;

    printk(KERN_INFO "%s successfully released\n", DEV_NAME);
    return 0;
}

/**
 * Module reading
 * \param file file struct
 * \param buf user buffer
 * \param buf_size size of buffer
 * \param pos offset
 * \return number of bytes read
 */
static ssize_t module_read(struct file *file, char __user *buf, size_t buf_size, loff_t *pos) {
    char *buffer = file->private_data;
    int bytes_amount = buf_size - copy_to_user(buf, buffer + *pos, buf_size);
    *pos += bytes_amount;

    printk(KERN_INFO "%s successfully read %d bytes from %d position\n", DEV_NAME, bytes_amount, (int) *pos);
    return bytes_amount;
}

/**
 * Module writing
 * \param file file struct
 * \param buf user buffer
 * \param buf_size size of buffer
 * \param pos offset
 * \return number of bytes written
 */
static ssize_t module_write(struct file *file, const char __user *buf, size_t buf_size, loff_t *pos) {
    char *buffer = file->private_data;
    int bytes_amount = buf_size - copy_from_user(buffer + *pos, buf, buf_size);
    *pos += bytes_amount;

    printk(KERN_INFO "%s successfully wrote %d bytes from %d position\n", DEV_NAME, bytes_amount, (int) *pos);
    return bytes_amount;
}

static const struct file_operations cdev_file_operations = {
    .owner = THIS_MODULE,
    .read = module_read,
    .write = module_write,
    .open = module_open,
    .release = module_release
};

/**
 * Module initialization
 * \return status code
 */
static int __init lkm_init(void) {
    dev_t dev;
    int code_status;
    code_status = alloc_chrdev_region(&dev, dev_minor, 1, DEV_NAME);
    if (code_status) {
        printk(KERN_ERR "%s could not successfully registered\n", DEV_NAME);
        return code_status;
    }

    dev_major = MAJOR(dev);

    class = class_create(THIS_MODULE, DEV_NAME);
    if (IS_ERR(class)) {
        unregister_chrdev_region(dev, 1);
        printk(KERN_ERR "%s class could not successfully registered\n", THIS_MODULE->name);
        return PTR_ERR(class);
    }

    device = device_create(class, NULL, MKDEV(dev_major, dev_minor), NULL, DEV_NAME);
    if (IS_ERR(device)) {
        class_destroy(class);
        unregister_chrdev_region(dev, 1);
        printk(KERN_ERR "%s defice could not successfully created\n", THIS_MODULE->name);
        return PTR_ERR(device);
    }

    printk(KERN_INFO "/dev/%s successfully created with major = %d and minor = %d\n", 
        THIS_MODULE->name, dev_major, dev_minor);
    return 0;
}

/**
 * Module unloading
 */
static void __exit lkm_exit(void) {
    dev_t dev = MKDEV(dev_major, dev_minor);
    device_destroy(class, dev);
    // cdev_del(cdev);
    class_unregister(class);
    class_destroy(class);
    unregister_chrdev_region(dev, 1);
    printk(KERN_INFO "%s successfully unregistered\n", DEV_NAME);
}

MODULE_LICENSE("GPL");

module_init(lkm_init);
module_exit(lkm_exit);
