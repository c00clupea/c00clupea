/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 * 
 * File:	gheader.h
 * created: 	Mon Feb 23 10:41:30 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#ifndef GUARDIAN_MODULE_H
#define GUARDIAN_MODULE_H


#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>  
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <generated/autoconf.h>
#include "../conf.h"

#define TRUE 1
#define FALSE 0
#define ERROR -1

#define P_FLAG 0x00010000 /*same than X86_CR0_WP see http://www.cs.fsu.edu/~baker/devices/lxr/http/source/linux/include/asm-x86/processor-flags.h?v=2.6.25.8#L35*/

#ifdef C00VERBOSE
#define C00TRACE(fmt,...) printk(fmt, ##__VA_ARGS__)
#else
#define C00TRACE(fmt,...)
#endif


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

#if ARCHDETECTED == X86_64
extern unsigned long *ia32_syscalltable;
#endif
extern unsigned long *syscalltable;

/*The syscalls*/
extern asmlinkage long (*org_sys_write)(unsigned int fd, const char __user *buf, size_t count);
extern asmlinkage long (*org_sys_read)(unsigned int fd, char __user *buf, size_t count);

void *memmem ( const void *haystack, size_t haystack_size, const void *needle, size_t needle_size );

unsigned long *obtain_syscalltable(void);

#if ARCHDETECTED == X86_64
unsigned long *obtain_ia32_syscalltable(void);
#endif

#endif /* GUARDIAN_MODULE_H */


