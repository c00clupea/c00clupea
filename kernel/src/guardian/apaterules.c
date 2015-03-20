/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	apaterules.c
 * created: 	Mon Mar 16 11:31:32 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */

#include "guardian_module.h"

inline int c00_rules_open(const char* file, int flags, int mode)
{
#ifdef NORULES
  return org_sys_open(file,flags,mode);
#else
  int ret;
  sopen_call_orig(file,flags,mode,&ret);
  //  ret =  org_sys_open(file,flags,mode);
  sopen_log_post(file,flags,mode,ret);
  //  c00_log_dyn(1,"open file %s as %d with f: %d\n",file,ret,flags);
  return ret;
#endif
}


inline long c00_rules_read(int fd, void __user *buf, size_t count)
{
#ifdef NORULES
  return org_sys_read(fd,buf,count);
#else
  long ret;
  sread_log_pre(fd,count);
  sread_call_orig(fd,buf,count,&ret);
  return ret;
#endif
}


long c00_rules_write(int fd, const void __user *buf, size_t count){
#ifdef NORULES
  return org_sys_write(fd,buf,count);
#else
  long ret;
  /**###########################
   * This looks creepy, however....
   **###########################
   *  the buffer is constant, we need to copy it...
   *  This can be a problem with performance...for this we need some decision when to copy...
   * <*))><
   */
#ifdef _MAKE_BUF_COPYABLE_
  void __user *buffer;
  buffer = kmalloc((count * sizeof(char)),GFP_KERNEL);
  if(!buffer){
    ret = 0;
    goto error;
  }
  memcpy(buffer,buf,(count * sizeof(char));
#else
  const void __user *buffer;
  buffer = buf;
#endif
  swrite_call_orig(fd,buffer,count,&ret);
  swrite_log_post(fd,buffer,count,ret);
  

#ifdef _MAKE_BUF_COPYABLE_
  kfree(buffer);
error:
#endif

  return ret;
#endif
}
