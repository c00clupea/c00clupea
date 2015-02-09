/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 * 
 * File:	c00s_nice.h
 * created: 	Mon Feb  9 11:13:14 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#ifndef C00S_NICE_H
#define C00S_NICE_H
#include "include/c00s_libcu.h"

#ifdef C00SWITHLINK
#define NICE_MAIN nice_main
#else
#define NICE_MAIN main
#endif

int NICE_MAIN(int argc, char *argv[]);


#endif /* C00S_NICE_H */
