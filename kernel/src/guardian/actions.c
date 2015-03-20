/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	actions.c
 * created: 	Sun Mar 15 12:09:12 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#include "guardian_module.h"

inline int sopen_mod_param(char *file, int *flags, int *mode){
  return TRUE; //Placeholder as prototype
}
inline int sopen_log_pre(const char *file, int flags, int mode){
  c00_log_dyn(1,"open %s %d %d pre\n",file,flags,mode);
  return TRUE;
}
inline int sopen_log_post(const char *file, int flags, int mode, int ret){
  c00_log_dyn(1,"open %s %d %d %d post\n",file,flags,mode,ret);
  return TRUE;
}
inline int sopen_call_orig(const char *file, int flags, int mode, int *ret){
  int condc = 0;
  testwithconditions(&condc);
  *ret = org_sys_open(file,flags,mode);
  c00_log_dyn(1,"open %s %d %d %d %d call\n",file,flags,mode,*ret,condc);
  return TRUE;
}
inline int sopen_mod_return(int *ret){
  return TRUE; //Placeholder as prototype
}


inline int sread_mod_param(int *fd, void __user *buf, size_t *count)
{
  return TRUE;
}

inline int sread_log_pre(int fd, size_t count)
{
  int condc = 0;
  testwithconditions(&condc);
  c00_log_dyn(1,"read%d:%d:%d\n",fd,count,condc);
  //printk("read %d:%d\n",fd,count);
  return TRUE;
}

inline int sread_log_post(int fd, const void __user *buf, size_t count, long ret)
{
  char *buffer;
  buffer = kmalloc((count +1)*sizeof(char), GFP_KERNEL);
  if(!buffer){
    goto error;
  }
  strlcpy(buffer,(char *)buf,count);
  c00_log_dyn(1,"read %d:%d:%d:%s\n",fd,count,ret,buf);
  kfree(buffer);
  return TRUE;
 error:
  return ERROR;
}

inline int sread_call_orig(int fd,void __user *buf, size_t count, long *ret)
{
  *ret = org_sys_read(fd,buf,count);
  return TRUE;
}


inline int sread_mod_return(long *ret)
{
  return TRUE;
}


int swrite_mod_param(int *fd,_CP_BUF void __user *buf, size_t *count){
  return TRUE;
}
int swrite_log_pre(int fd,_CP_BUF void __user *buf, size_t count){
  c00_log_dyn(1,"write %d,%d\n",fd,count);
  return TRUE;
}
int swrite_log_post(int fd,_CP_BUF void __user *buf, size_t count,long ret){
 int condc = 0;
  testwithconditions(&condc);

  c00_log_dyn(1,"write %d,%d,%d\n",fd,count,condc);
  return TRUE;
}
int swrite_call_orig(int fd,_CP_BUF void __user *buf, size_t count, long *ret){
*ret =  org_sys_write(fd,buf,count);
 return TRUE;
}
int swrite_mod_return(long *ret){
  return TRUE;
}
