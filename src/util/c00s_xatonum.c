/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	c00s_xatonum.c
 * created: 	Thu Nov 27 09:10:42 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */

#include "include/c00s_libcu.h"

static inline int __in_range(long val, long min, long max);
static inline int __basic_strol(const char *args, long *val, long min, long max);

static unsigned long long ret_ERANGE(void)
{
    errno = ERANGE; /* this ain't as small as it looks (on glibc) */
    return ULLONG_MAX;
}



static unsigned long long handle_errors(unsigned long long v, char **endp)
{
    char next_ch = **endp;

    /* errno is already set to ERANGE by strtoXXX if value overflowed */
    if (next_ch) {
        /* "1234abcg" or out-of-range? */
        if (isalnum(next_ch) || errno)
            return ret_ERANGE();

        /* good number, just suspicious terminator */
        errno = EINVAL;
    }

    return v;
}


long long bb_strtoll(const char *arg, char **endp, int base)
{
    unsigned long long v;
    char *endptr;
    char first;

    if (!endp) endp = &endptr;

    *endp = (char *) arg;
    /* Check for the weird "feature":
     * a "-" string is apparently a valid "number" for strto[u]l[l]!
     * It returns zero and errno is 0! :( */
    first = (arg[0] != '-' ? arg[0] : arg[1]);

    if (!isalnum(first)) return ret_ERANGE();

    errno = 0;
    v = strtoll(arg, endp, base);
    return handle_errors(v, endp);
}

unsigned long long FAST_FUNC bb_strtoull(const char *arg, char **endp, int base)
{
    unsigned long long v;
    char *endptr;

    if (!endp) endp = &endptr;

    *endp = (char *) arg;

    /* strtoul("  -4200000000") returns 94967296, errno 0 (!) */
    /* I don't think that this is right. Preventing this... */
    if (!isalnum(arg[0])) return ret_ERANGE();

    /* not 100% correct for lib func, but convenient for the caller */
    errno = 0;
    v = strtoull(arg, endp, base);
    return handle_errors(v, endp);
}

int __in_range(long val, long min, long max)
{
    if(val >= min && val <= max) {
        return TRUE;
    }

    return FALSE;
}

int c00_strtoipos(const char *args, int *val)
{
    if(c00_strtoi(args, val) != TRUE) {
        return FALSE;
    }

    if(__in_range(*val, 0, INT_MAX) != TRUE) {
        printf("error2");
        return FALSE;
    }

    return TRUE;
}

int c00_strtolpos(const char *args, long *val)
{
    if(c00_strtol(args, val) != TRUE) {
        return FALSE;
    }

    if(__in_range(*val, 0, INT_MAX) != TRUE) {
        printf("error2");
        return FALSE;
    }

    return TRUE;
}

int __basic_strol(const char *args, long *val, long min, long max)
{
    check(args, "%s should not be null", "args");
    char *end;
    *val = strtol(args, &end, 10);

    if(end == args) {
        *val = 0;
        //not dec
        return ERROR;
    }
    else if('\0' != *end) {
        *val = 0;
        //something wrong in string
        return ERROR;
    }
    else if(!__in_range(*val, min, max)) {
        *val = 0;
        //out of range
        return ERROR;
    }

    return TRUE;
error:
    return ERROR;
}

int c00_strtoi_in_range(const char *args, int *val, long min, long max)
{
    long v1;

    if(__basic_strol(args, &v1, min, max) != TRUE) {
        *val = 0;
        return ERROR;
    }

    *val = (int)v1;
    return TRUE;
}

int c00_strtoi(const char *args, int *val)
{
    long v1;

    if(__basic_strol(args, &v1, INT_MIN, INT_MAX) != TRUE) {
        *val = 0;
        return ERROR;
    }

    *val = (int)v1;
    return TRUE;
}

int c00_strtol(const char *args, long *val)
{
    long v1;

    if(__basic_strol(args, &v1, LONG_MIN, LONG_MAX) != TRUE) {
        *val = 0;
        return ERROR;
    }

    *val = v1;
    return TRUE;
}


unsigned FAST_FUNC bb_strtou(const char *arg, char **endp, int base)
{
    unsigned long v;
    char *endptr;

    if (!endp) endp = &endptr;

    *endp = (char *) arg;

    if (!isalnum(arg[0])) return ret_ERANGE();

    errno = 0;
    v = strtoul(arg, endp, base);

    if (v > UINT_MAX) return ret_ERANGE();

    return handle_errors(v, endp);
}


int bb_strtoi(const char *arg, char **endp, int base)
{
    return bb_strtoll(arg, endp, base);
}

unsigned long bb_strtoul(const char *arg, char **endp, int base)
{
    return bb_strtoull(arg, endp, base);
}
