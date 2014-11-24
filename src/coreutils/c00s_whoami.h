#ifndef C00S_WHOAMI_H
#define C00S_WHOAMI_H
/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	c00s_whoami.h
 * created: 	Sat Aug 30 12:40:44 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include "../global.h"

#ifdef C00SWITHLINK
#define WHOAMI_MAIN whoami_main
#else
#define WHOAMI_MAIN main
#endif

int WHOAMI_MAIN(int argc, char *argv[]);


#endif /* C00S_WHOAMI_H */
