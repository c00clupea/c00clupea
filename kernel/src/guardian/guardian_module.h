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

/*#ifndef GUARDIAN_MODULE_H
#define GUARDIAN_MODULE_H
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>  
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/netpoll.h>
#include <linux/inet.h>
/*#include <generated/autoconf.h>*/


#define TRUE 1
#define FALSE 0
#define ERROR -1


#ifndef _LOCIP
#define _LOCIP "127.0.0.1" /*127.0.0.1*/
#endif

#ifndef _EXTIP
#define _EXTIP "127.0.0.1" /*127.0.0.1*/
#endif

#ifndef _LOCPORT
#define _LOCPORT 6666
#endif

#ifndef _EXTPORT
#define _EXTPORT 4242
#endif

#ifndef _IFDEV
#define _IFDEV "eth0"
#endif

#define _STAT_BUF_SIZE 64

//#define _MAKE_BUF_COPYABLE_ 1

#define P_FLAG 0x00010000 /*same than X86_CR0_WP see http://www.cs.fsu.edu/~baker/devices/lxr/http/source/linux/include/asm-x86/processor-flags.h?v=2.6.25.8#L35*/

#ifdef _C00_VERBOSE_
#define C00TRACE(fmt,...) printk(fmt, ##__VA_ARGS__)
#else
#define C00TRACE(fmt,...)
#endif

#define C00LOG(lvl,msg) c00_log(lvl,msg)



#define c00_log_sys(lvl,name,...) c00_log_dyn(lvl,)

struct c00_logconf{
  const char *local_ip;
  const char *target_ip;
  int local_port;
  int target_port;
  const char *device;
};

#ifdef _X86_64_
extern unsigned long *ia32_syscalltable;
#endif
extern unsigned long *syscalltable;

/*The syscalls*/
extern asmlinkage long (*org_sys_write)(int fd, const void __user *buf, size_t count);
extern asmlinkage long (*org_sys_read)(int fd, void __user *buf, size_t count);
extern asmlinkage int (*org_sys_open)(const char* file, int flags, int mode);

extern asmlinkage int (*org_sys_close)(int fd);

/*The hooks*/
extern asmlinkage long (*hook_sys_write)(int fd, const void __user *buf, size_t count);
extern asmlinkage long (*hook_sys_read)(int fd, void __user *buf, size_t count);
extern asmlinkage int (*hook_sys_open)(const char* file, int flags, int mode);

extern asmlinkage int (*hook_sys_close)(int fd);
void *memmem ( const void *haystack, size_t haystack_size, const void *needle, size_t needle_size );

asmlinkage int concrete_hook_sys_open(const char* file, int flags, int mode);
asmlinkage long concrete_hook_sys_read(int fd, void __user *buf, size_t count);
asmlinkage long concrete_hook_sys_write(int fd, const void __user *buf, size_t count);
asmlinkage int concrete_hook_sys_close(int fd);


/*some convenience globals*/


extern struct netpoll *np;
extern struct netpoll np_t;
extern struct c00_logconf logconf_t;
extern struct c00_logconf *logconf_p;

/*some util functions*/
int c00_log_init(struct c00_logconf *logconf);
int c00_log(unsigned int lvl,const char* buf);

int c00_log_dyn(unsigned int lvl, const char* fmt,...);

/*rules*/
//int c00_fst_strlen(const char *buf);

#define SHORTIF(a) (a == TRUE)

int cond_eq_int(int a, int b);
int cond_eq_str(const char *a, const char *b);


/*actions*/
/*sys_open*/
int sopen_mod_param(char *file, int *flags, int *mode);
int sopen_log_pre(const char *file, int flags, int mode);
int sopen_log_post(const char *file, int flags, int mode, int ret);
int sopen_call_orig(const char *file, int flags, int mode, int *ret);
int sopen_mod_return(int *ret);

/*sys_read*/
int sread_mod_param(int *fd, void __user *buf, size_t *count);
int sread_log_pre(int fd, size_t count);
int sread_log_post(int fd, const void __user *buf, size_t count, long ret);
int sread_call_orig(int fd,void __user *buf, size_t count, long *ret);
int sread_mod_return(long *ret);

#ifdef _MAKE_BUF_COPYABLE_
#define _CP_BUF 
#else
#define _CP_BUF const
#endif
int swrite_mod_param(int *fd,_CP_BUF void __user *buf, size_t *count);
int swrite_log_pre(int fd,_CP_BUF void __user *buf, size_t count);
int swrite_log_post(int fd,_CP_BUF void __user *buf, size_t count,long ret);
int swrite_call_orig(int fd,_CP_BUF void __user *buf, size_t count, long *ret);
int swrite_mod_return(long *ret);


/*rules*/
int c00_rules_open(const char* file, int flags, int mode);
long c00_rules_read(int fd, void __user *buf, size_t count);
long c00_rules_write(int fd, const void __user *buf, size_t count);

unsigned long *obtain_syscalltable(void);

int testwithconditions(int *count);


#ifdef _X86_64_
unsigned long *obtain_ia32_syscalltable(void);
#endif
/*
#endif  GUARDIAN_MODULE_H 
*/

