#ifndef C00S_UPTIME_H
#define C00S_UPTIME_H
/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	c00s_uptime.h
 * created: 	Sat Aug 30 18:37:56 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */

#include "../util/busybox_cccc.h"
#include <time.h>
#ifdef __linux__
#include <sys/sysinfo.h>
#endif

int uptime_main(int argc, char *argv[]);


#endif /* C00S_UPTIME_H */
