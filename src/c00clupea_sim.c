/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	c00clupea_sim.c
 * created: 	Wed Sep 10 23:10:29 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */

#include "c00clupea_sim.h"

static inline int call_coreutil(int argc, char *argv[]);

int main(int argc, char *argv[]) {
	
	return call_coreutil(argc,argv);
}

int call_coreutil(int argc, char *argv[]){
	C00DEBUG("Call: %s",argv[0]);
	#ifdef C00SUNAME
	check_box(uname,"c00_uname");
	#endif
	#ifdef C00SWHOAMI
	check_box(whoami,"c00_whoami");
	#endif
	#ifdef C00SUPTIME
	check_box(uptime,"c00_uptime");
	#endif

	return ERROR;
	
}
