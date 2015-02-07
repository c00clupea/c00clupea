/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	c00s_strings.h
 * created: 	Fri Nov 28 13:42:23 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#ifndef C00S_STRINGS_H
#define C00S_STRINGS_H

#include "../util/busybox_cccc.h"


#ifdef C00SWITHLINK
#define STRINGS_MAIN strings_main
#else
#define STRINGS_MAIN main
#endif

#define WHOLE_FILE    1
#define PRINT_NAME    2
#define PRINT_OFFSET  4
#define SIZE          8


int STRINGS_MAIN(int UNUSED(argc), char *argv[]);
/**#####################
 * This is a bloody Hack
 **#####################
 *  be careful with argv....this is possibly a bug
 * <*))><
 */


#endif /* C00S_STRINGS_H */
