/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	c00s_process_escaping.c
 * created: 	Sat Feb  7 10:11:27 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#include "util/busybox_cccc.h"


#define WANT_HEX_ESCAPES 1

/* Usual "this only works for ascii compatible encodings" disclaimer. */
#undef _tolower
#define _tolower(X) ((X)|((char) 0x20))

char FAST_FUNC bb_process_escape_sequence(const char **ptr)
{
    const char *q;
    unsigned num_digits;
    unsigned n;
    unsigned base;
    num_digits = n = 0;
    base = 8;
    q = *ptr;

    if (WANT_HEX_ESCAPES && *q == 'x') {
        ++q;
        base = 16;
        ++num_digits;
    }

    /* bash requires leading 0 in octal escapes:
     * \02 works, \2 does not (prints \ and 2).
     * We treat \2 as a valid octal escape sequence. */
    do {
        unsigned r;
#if !WANT_HEX_ESCAPES
        unsigned d = (unsigned char)(*q) - '0';
#else
        unsigned d = (unsigned char)_tolower(*q) - '0';

        if (d >= 10)
            d += ('0' - 'a' + 10);

#endif

        if (d >= base) {
            if (WANT_HEX_ESCAPES && base == 16) {
                --num_digits;

                if (num_digits == 0) {
                    /* \x<bad_char>: return '\',
                     * leave ptr pointing to x */
                    return '\\';
                }
            }

            break;
        }

        r = n * base + d;

        if (r > UCHAR_MAX) {
            break;
        }

        n = r;
        ++q;
    }
    while (++num_digits < 3);

    if (num_digits == 0) {
        /* Not octal or hex escape sequence.
         * Is it one-letter one? */
        /* bash builtin "echo -e '\ec'" interprets \e as ESC,
         * but coreutils "/bin/echo -e '\ec'" does not.
         * Manpages tend to support coreutils way.
         * Update: coreutils added support for \e on 28 Oct 2009. */
        static const char charmap[] ALIGN1 = {
            'a',  'b', 'e', 'f',  'n',  'r',  't',  'v',  '\\', '\0',
            '\a', '\b', 27, '\f', '\n', '\r', '\t', '\v', '\\', '\\',
        };
        const char *p = charmap;

        do {
            if (*p == *q) {
                q++;
                break;
            }
        }
        while (*++p != '\0');

        /* p points to found escape char or NUL,
         * advance it and find what it translates to.
         * Note that \NUL and unrecognized sequence \z return '\'
         * and leave ptr pointing to NUL or z. */
        n = p[sizeof(charmap) / 2];
    }

    *ptr = q;
    return (char) n;
}
