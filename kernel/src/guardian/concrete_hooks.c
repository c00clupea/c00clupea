/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 * 
 * File:	concrete_hooks.c
 * created: 	Mon Feb 23 17:19:57 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#include "guardian_module.h"

asmlinkage int concrete_hook_sys_open(const char* file, int flags, int mode)
{
  int ret;
  printk("open file %s\n",file);

  ret = org_sys_open(file,flags,mode);
  return ret;
}

asmlinkage long concrete_hook_sys_read(unsigned int fd, char __user *buf, size_t count)
{
  long ret;
  printk("Read %d, c: %d\n",fd,count);
  ret = org_sys_read(fd,buf,count);
  return ret;
}

asmlinkage long concrete_hook_sys_write(unsigned int fd, char __user *buf, size_t count)
{
  long ret;
  printk("Write %d, c: %d\n",fd,count);
  ret = org_sys_write(fd,buf,count);
  return ret;
}
