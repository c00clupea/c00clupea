/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	c00s_cat.c
 * created: 	Thu Nov 27 12:21:16 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#include "c00s_cat.h"

static inline int c00_cat(char **argv);


int c00_cat(char **argv)
{
    int fd;
    int retval = TRUE;

    if(!*argv) {
        argv = (char **) &bb_argv_dash;
    }

    do {
        fd = open_or_warn_stdin(*argv);

        if (fd >= 0) {
            off_t r = bb_copyfd_eof(fd, STDOUT_FILENO);

            if (fd != STDIN_FILENO) {
                close(fd);
            }

            if (r >= 0) {
                continue;
            }
        }

        retval = ERROR;
    }
    while (*++argv);

    return retval;
}

int CAT_MAIN(int UNUSED(argc), char *argv[])
{
    getopt32(argv, "u");
//	printf("reach 2");
    argv += optind;
    return c00_cat(argv);
//	return TRUE;
}
