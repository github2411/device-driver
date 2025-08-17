#include <linux/init.h>
#include <linux/modules.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL"); //*
MODULE_AUTHOR("afrin momin"); //!
MODULE_DESCRIPTION("readlodable kernel module"); //!

static struct proc_dir_entry *custom_proc_node;

static ssize_t afrin_read(struct file* file_pointer,
                          char *user_space_buffer,
                        size_t count,
                        loff_t* offset) {
        printk("afrin_read\n");
        return 0;
}

struct proc_ops driver_proc_ops={
    .proc_read = afrin_read
};

static int afrin_module_init(void){
    printk("afrin_module_init:entry\n");

    custom_proc_node = proc_create("afrin_driver",
                                    0,
                                NULL,
                                &driver_proc_ops);
    if(custom_proc_node==NULL){
        printk("frin_module_init:error\n");
        return -1;
    }
    printk("afrin_module_init:exit\n");
    return 0;
}

static void afrin_module_exit(void){
    printk("afrin_module_exit:entry\n");
    proc_remove(custom_proc_node);
    printk("afrin_module_exit:exit\n");
}

module_init(afrin_module_init);
module_exit(afrin_module_exit);
