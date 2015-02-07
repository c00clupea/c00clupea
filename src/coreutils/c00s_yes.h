/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	c00s_yes.h
 * created: 	Fri Nov 28 11:56:24 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#ifndef C00S_YES_H
#define C00S_YES_H

#include <stdarg.h>

#include "../util/busybox_cccc.h"

#ifdef C00SWITHLINK
#define YES_MAIN yes_main
#else
#define YES_MAIN main
#endif

int YES_MAIN(int argc, char *argv[]);

#endif /* C00S_YES_H */
