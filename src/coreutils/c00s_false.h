/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	c00s_false.h
 * created: 	Fri Nov 28 11:07:56 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#ifndef C00S_FALSE_H
#define C00S_FALSE_H

#include "include/c00s_libcu.h"

#ifdef C00SWITHLINK
#define FALSE_MAIN false_main
#else
#define FALSE_MAIN main
#endif

int FALSE_MAIN(int UNUSED(argc), char UNUSED(*argv[]));


#endif /* C00S_TRUE_H */
