/**
 *
 * Some sourcecode in this file is shamelessly copied from another open source software
 * See the original license and developers below this header
 * However other parts in this sourcefile are adopted for the c00clupea Honeypot
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 */
#ifndef C00S_XATONUM_H
#define C00S_XATONUM_H

#include "include/c00s_libcu.h"

int c00_strtoi(const char *args, int *val);
int c00_strtoipos(const char *args, int *val);
int c00_strtol(const char *args, long *val);
int c00_strtolpos(const char *args, long *val);
int c00_strtoi_in_range(const char *args, int *val, long min, long max);
unsigned bb_strtou(const char *arg, char **endp, int base) FAST_FUNC;
long long bb_strtoll(const char *arg, char **endp, int base) FAST_FUNC;
int bb_strtoi(const char *arg, char **endp, int base);
unsigned long long bb_strtoull(const char *arg, char **endp, int base) FAST_FUNC;
unsigned long bb_strtoul(const char *arg, char **endp, int base);


#endif /* C00S_XATONUM_H */
