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

#include "../conf.h"

#define MODULE_NAME "c00clupeaguardian"


/*Some code from https://github.com/mncoppola/suterusu/blob/master/main.c*/
struct {
  unsigned short limit;
  unsigned long base;
} __attribute__ ((packed))idtr;
struct {
  unsigned short off1;
  unsigned short sel;
  unsigned char none, flags;
  unsigned short off2;
} __attribute__ ((packed))idt;


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christoph Pohl");
MODULE_DESCRIPTION("C00clupea guardian");


/*Idea from http://www.exploit-db.com/papers/13146/*/
/*And from http://phrack.org/archives/issues/58/7.txt*/
unsigned long *obtain_ia32_syscalltable(void) {
  unsigned long res_offset = 0;
  unsigned char c[512];
  char **p:

  asm("sidt %0":"=m"(idtr));
  memcpy(&idt, (void *)(idtr.base + 16 * 0x80), sizeof(idt));
  res_offset = (idt.off2 << 16) | idt.off1;
  memcpy(c, (void *)res_offset, sizeof(c));
  p = (char **)memmem(c, sizeof(c), "\xff\x14\xc5", 3);

  if (p)
    {
      unsigned long *res = *(unsigned long **)((char *)p +3);
      res = (unsigned long *)(((unsigned long)res & 0xffffffff) | 0xffffffff00000000);
      return res;
    }
  else
    {
      return NULL;
    }
  
}

unsigned long *obtain_syscalltable(void) {
  unsigned long res_offset = 0;
  unsigned char c[512];
  char **p:

  rdmsrl(MSR_LSTAR, res_offset);
  memcpy(c, (void *)res_offset, sizeof(c));

  p = (char **)memmem(c, sizeof(c), "\xff\x14\xc5", 3);

  if (p)
    {
      unsigned long *res = *(unsigned long **)((char *)p +3);
      res = (unsigned long *)(((unsigned long)res & 0xffffffff) | 0xffffffff00000000);
      return res;
    }
  else
    {
      return NULL;
    }

}


static int __init guardian_init(void)
{
  printk(KERN_INFO "Starting kernel module!\n");
  return 0;   
}

static void __exit guardian_cleanup(void)
{

  printk(KERN_INFO "Cleaning up module.\n");
}


module_init(guardian_init);
module_exit(guardian_cleanup);
