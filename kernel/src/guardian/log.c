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
  np_t.local_ip.ip = htonl(logconf->local_ip);
  np_t.local_ip.in.s_addr = htonl(logconf->local_ip);
  np_t.remote_ip.ip = htonl(logconf->target_ip);
  np_t.remote_ip.in.s_addr = htonl(logconf->target_ip);
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

