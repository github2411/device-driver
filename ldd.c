#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL"); //*
MODULE_AUTHOR("afrin momin"); //!
MODULE_DESCRIPTION("readlodable kernel module"); //!

static struct proc_dir_entry *custom_proc_node;

static ssize_t afrin_read(struct file* file_pointer,
                          char *user_space_buffer,        //user_space_buffer is used to store the msg send to user from kernel driver
                        size_t count,
                        loff_t* offset) {
        char msg[] = "Ack!\n";
        size_t len= strlen(msg);
        int result;

        printk("afrin_read\n");

        if(*offset >= len){
            return 0;
        }

        result=copy_to_user(user_space_buffer,msg,len);
        *offset=len;    

        return len;
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
