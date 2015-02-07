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
/* vi: set sw=4 ts=4: */
/* uname -- print system information
 * Copyright (C) 1989-1999 Free Software Foundation, Inc.
 *
 * Licensed under GPLv2 or later, see file LICENSE in this source tree.
 */

/* BB_AUDIT SUSv3 compliant */
/* http://www.opengroup.org/onlinepubs/007904975/utilities/uname.html */

#ifndef C00S_UNAME_H
#define C00S_UNAME_H
#include "../util/busybox_cccc.h"
#include <stddef.h>
#include <sys/utsname.h>

typedef struct {
	struct utsname name;
	char processor[sizeof(((struct utsname*)NULL)->machine)];
	char platform[sizeof(((struct utsname*)NULL)->machine)];
	char os[sizeof("GNU/Linux")];
} uname_info_t;


static const char options[] = "snrvmpioa";
static const unsigned short utsname_offset[] = {
	offsetof(uname_info_t, name.sysname), /* -s */
	offsetof(uname_info_t, name.nodename), /* -n */
	offsetof(uname_info_t, name.release), /* -r */
	offsetof(uname_info_t, name.version), /* -v */
	offsetof(uname_info_t, name.machine), /* -m */
	offsetof(uname_info_t, processor), /* -p */
	offsetof(uname_info_t, platform), /* -i */
	offsetof(uname_info_t, os), /* -o */
};

#ifdef C00SWITHLINK
#define UNAME_MAIN uname_main
#else
#define UNAME_MAIN main
#endif

int UNAME_MAIN(int argc, char *argv[]);

#endif
