/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 * 
 * File:	c00s_touch.h
 * created: 	Mon Feb  9 10:09:35 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#ifndef C00S_TOUCH_H
#define C00S_TOUCH_H
#include "include/c00s_libcu.h"

#ifdef C00SWITHLINK
#define TOUCH_MAIN touch_main
#else
#define TOUCH_MAIN main
#endif

int TOUCH_MAIN(int argc, char *argv[]);


#endif /* C00S_TOUCH_H */
