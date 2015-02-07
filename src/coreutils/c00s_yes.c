/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	c00s_yes.c
 * created: 	Fri Nov 28 11:56:46 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#include "c00s_yes.h"

int YES_MAIN(int UNUSED(argc), char *argv[])
{
    char **pp;
    argv[0] = (char *)"y";

    if(argv[1]) {
        ++argv;
    }

    do {
        pp = argv;

        while(1) {
            fputs(*pp, stdout);

            if(!*++pp) {
                break;
            }

            putchar(' ');
        }
    }
    while (putchar('\n') != EOF);

    return TRUE;
}
