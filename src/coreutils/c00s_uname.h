/*
 *Copyright (C) 2014-2014 Christoph Pohl
 *
 *Licensed under GPLv2 or later see file LICENSE in this source tree
 *
 *This source file is part of the c00clupea honeypot system
 *However most of the code is copied from busybox, also under GPLv2
 *Just the relevant parts for honeypots are changed...
 */

#ifndef C00S_UNAME_H
#define C00S_UNAME_H
#include "../global.h"
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

int uname_main(int argc, char *argv[]);

#endif
