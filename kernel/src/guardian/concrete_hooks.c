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
