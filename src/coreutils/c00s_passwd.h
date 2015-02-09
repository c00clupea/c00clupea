/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 * 
 * File:	c00s_passwd.h
 * created: 	Mon Feb  9 06:30:24 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#ifndef C00S_PASSWD_H
#define C00S_PASSWD_H
#include "include/c00s_libcu.h"

#ifdef C00SWITHLINK
#define PASSWD_MAIN passwd_main
#else
#define PASSWD_MAIN main
#endif

int PASSWD_MAIN(int argc, char *argv[]);

#endif /* C00S_PASSWD_H */
