/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 * 
 * File:	c00s_pwd.h
 * created: 	Mon Feb  9 10:50:12 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#ifndef C00S_PWD_H
#define C00S_PWD_H

#include "include/c00s_libcu.h"

#ifdef C00SWITHLINK
#define PWD_MAIN pwd_main
#else
#define PWD_MAIN main
#endif

int PWD_MAIN(int argc, char *argv[]);

#endif /* C00S_PWD_H */
