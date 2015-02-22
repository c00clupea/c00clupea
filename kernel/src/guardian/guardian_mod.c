/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 * 
 * File:	guardian_mod.c
 * created: 	Sun Feb 22 21:05:56 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */


#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>  
#include <linux/proc_fs.h>
#include <linux/sched.h>

#define MODULE_NAME "c00clupeaguardian"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christoph Pohl");
MODULE_DESCRIPTION("C00clupea guardian");

static int __init guardian_init(void)
{
  printk(KERN_INFO "Starting kernel module!\n");
  return 0;    // Non-zero return means that the module couldn't be loaded.
}

static void __exit guardian_cleanup(void)
{

  printk(KERN_INFO "Cleaning up module.\n");
}


module_init(guardian_init);
module_exit(guardian_cleanup);
