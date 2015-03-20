
/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	log.c
 * created: 	Thu Mar 12 16:15:08 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */

#include "guardian_module.h"

struct netpoll *np = NULL;
struct netpoll np_t;

int c00_log_init(struct c00_logconf *logconf){
  np_t.name = "LRNG";
  strlcpy(np_t.dev_name,logconf->device,IFNAMSIZ);
  np_t.local_ip.ip = in_aton(logconf->local_ip);
  np_t.local_ip.in.s_addr = in_aton(logconf->local_ip);
  np_t.remote_ip.ip = in_aton(logconf->target_ip);
  np_t.remote_ip.in.s_addr = in_aton(logconf->target_ip);
  np_t.ipv6 = 0;
  np_t.local_port = logconf->local_port;
  np_t.remote_port = logconf->target_port;
  memset(np_t.remote_mac, 0xff, ETH_ALEN);
  netpoll_print_options(&np_t);
  netpoll_setup(&np_t);
  np = &np_t;
  return TRUE;
}


int c00_log(unsigned int lvl,const char* buf){
  int len = strlen(buf);
  netpoll_send_udp(np,buf,len);
  return TRUE;
}

int c00_log_dyn(unsigned int lvl, const char *fmt,...)
{
  int len;
  char buf[_STAT_BUF_SIZE];
  char *buffer;
  va_list args;
  va_start(args,fmt);
  len = vsnprintf(NULL,0,fmt,args);
  va_end(args); //Looks creepy but according to C99 one must stop and restart va_args when passwd as argument
  if((len+1)>_STAT_BUF_SIZE){
    buffer = kmalloc((len+1)*sizeof(char),GFP_KERNEL);
    if(!buffer){
      goto error;
    }
  }
  else{
    buffer = buf;
  }
  va_start(args,fmt);
  vsnprintf(buffer,len+1,fmt,args);
  C00LOG(lvl,buffer);
  va_end(args);
  
  if((len+1)>_STAT_BUF_SIZE){
    kfree(buffer);
  }
  return TRUE;
 error:
  return ERROR;
}
