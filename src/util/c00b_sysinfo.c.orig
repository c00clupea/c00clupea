/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	c00b_sysinfo.c
 * created: 	Sat Nov 24 18:37:56 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */

#include "c00b_sysinfo.h"

int c00b_sysinfo (struct c00b_sysinfo *__info){
	__info->uptime = 12345;

	//The load in SD needs to be divided through 65536 This is done in the shifting LOAD_INT and LOAD_FRAC

	__info->loads[0] = (unsigned)100000;
	__info->loads[1] = (unsigned)22312;
	__info->loads[2] = (unsigned)32312;


	return 0;
}


