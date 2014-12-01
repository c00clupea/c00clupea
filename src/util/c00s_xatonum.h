/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 * 
 * File:	c00s_xatonum.h
 * created: 	Thu Nov 27 09:09:54 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#ifndef C00S_XATONUM_H
#define C00S_XATONUM_H
#include "busybox_cccc.h"

int c00_strtoi(const char *args, int *val);
int c00_strtoipos(const char *args, int *val);
int c00_strtol(const char *args, long *val);
int c00_strtolpos(const char *args, long *val);
int c00_strtoi_in_range(const char *args, int *val, long min, long max);

#endif /* C00S_XATONUM_H */
