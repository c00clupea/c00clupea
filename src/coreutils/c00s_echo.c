/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	c00s_echo.c
 * created: 	Sat Feb  7 11:32:46 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#include "coreutils/c00s_echo.h"

int echo_main(int argc UNUSED_PARAM, char **argv)
{
    char **pp;
    const char *arg;
    char *out;
    char *buffer;
    unsigned buflen;
#if !ENABLE_FEATURE_FANCY_ECHO
    enum {
        eflag = '\\',
        nflag = 1,  /* 1 -- print '\n' */
    };
    argv++;
#else
    char nflag = 1;
    char eflag = 0;

    while ((arg = *++argv) != NULL) {
        char n, e;

        if (arg[0] != '-')
            break; /* not an option arg, echo it */

        /* If it appears that we are handling options, then make sure
         * that all of the options specified are actually valid.
         * Otherwise, the string should just be echoed.
         */
        arg++;
        n = nflag;
        e = eflag;

        do {
            if (*arg == 'n')
                n = 0;
            else if (*arg == 'e')
                e = '\\';
            else if (*arg != 'E') {
                /* "-ccc" arg with one of c's invalid, echo it */
                /* arg consisting from just "-" also handled here */
                goto just_echo;
            }
        }
        while (*++arg);

        nflag = n;
        eflag = e;
    }

just_echo:
#endif
    buflen = 0;
    pp = argv;

    while ((arg = *pp) != NULL) {
        buflen += strlen(arg) + 1;
        pp++;
    }

    out = buffer = xmalloc(buflen + 1); /* +1 is needed for "no args" case */

    while ((arg = *argv) != NULL) {
        int c;

        if (!eflag) {
            /* optimization for very common case */
            out = stpcpy(out, arg);
        }
        else
            while ((c = *arg++) != '\0') {
                if (c == eflag) {
                    /* This is an "\x" sequence */
                    if (*arg == 'c') {
                        /* "\c" means cancel newline and
                         * ignore all subsequent chars. */
                        goto do_write;
                    }

                    /* Since SUSv3 mandates a first digit of 0, 4-digit octals
                    * of the form \0### are accepted. */
                    if (*arg == '0') {
                        if ((unsigned char)(arg[1] - '0') < 8) {
                            /* 2nd char is 0..7: skip leading '0' */
                            arg++;
                        }
                    }

                    /* bb_process_escape_sequence handles NUL correctly
                     * ("...\" case). */
                    {
                        /* optimization: don't force arg to be on-stack,
                         * use another variable for that. ~30 bytes win */
                        const char *z = arg;
                        c = bb_process_escape_sequence(&z);
                        arg = z;
                    }
                }

                *out++ = c;
            }

        if (!*++argv)
            break;

        *out++ = ' ';
    }

    if (nflag) {
        *out++ = '\n';
    }

do_write:
    /* Careful to error out on partial writes too (think ENOSPC!) */
    errno = 0;
    /*r =*/ full_write(STDOUT_FILENO, buffer, out - buffer);
    free(buffer);

    if (/*WRONG:r < 0*/ errno) {
        bb_perror_msg(bb_msg_write_error);
        return 1;
    }

    return 0;
}

