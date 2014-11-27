/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 * 
 * File:	c00s_usleep.h
 * created: 	Thu Nov 27 06:28:38 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */

#ifndef C00S_USLEEP_H
#define C00S_USLEEP_H
#include "../util/busybox_cccc.h"
#include "../util/c00s_xatonum.h"
#include <unistd.h>


#ifdef C00SWITHLINK
#define USLEEP_MAIN usleep_main
#else
#define USLEEP_MAIN main
#endif

int USLEEP_MAIN(int argc, char *argv[]);

#endif /* C00S_USLEEP_H */
