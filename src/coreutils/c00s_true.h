/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 * 
 * File:	c00s_true.h
 * created: 	Fri Nov 28 11:07:56 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#ifndef C00S_TRUE_H
#define C00S_TRUE_H
#include "../util/busybox_cccc.h"


#ifdef C00SWITHLINK
#define TRUE_MAIN true_main
#else
#define TRUE_MAIN main
#endif

int TRUE_MAIN(int UNUSED(argc), char UNUSED(*argv[]));


#endif /* C00S_TRUE_H */
