
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
   
  ret = org_sys_open(file,flags,mode);

  c00_log_dyn(1,"open file %s as %d with f: %d\n",file,ret,flags);

  return ret;
}

asmlinkage long concrete_hook_sys_read(int fd, void __user *buf, size_t count)
{
  long ret;
char *buffer;
  //printk("Read %d, c: %ul\n",fd,count);
  ret = org_sys_read(fd,buf,count);



  //We do not know if the buffer is terminated...so we need to copy it
  buffer = kmalloc((count+1)*sizeof(char),GFP_KERNEL);
  if(!buffer){
    goto error;
  }
  strlcpy(buffer,(char *)buf,count);
  c00_log_dyn(1,"Read from %d:%d : %s\n --> %d",fd,count,buffer,ret);
  kfree(buffer);

 error:
  return ret;
  
}

asmlinkage long concrete_hook_sys_write(int fd, const void __user *buf, size_t count)
{
  long ret;
  char *buffer;

  //We do not know if the buffer is terminated...so we need to copy it
  buffer = kmalloc((count+1)*sizeof(char),GFP_KERNEL);
  if(!buffer){
    goto error;
  }
  strlcpy(buffer,(char *)buf,count);
  

  ret = org_sys_write(fd,buf,count);
  c00_log_dyn(1,"Write %d, %d, %s --> %d\n ",fd,count,buffer,ret);
  
  kfree(buffer);
  return ret;
 error:
  return ERROR;
}

asmlinkage int concrete_hook_sys_close(int fd)
{
  int ret;
  //  printk("Write %d, c: %d\n",fd,count);
  //  printk("Close %d\n",fd);
  ret = org_sys_close(fd);
  c00_log_dyn(1,"Close %d --> %d\n",fd,ret);
  return ret;
}


