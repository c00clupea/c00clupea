/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 * 
 * File:	c00s_pwd_.c
 * created: 	Tue Feb  3 16:30:01 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */

#include "c00s_pwd_.h"

/*#include "../util/busybox_cccc.h"*/

extern struct passwd *getpwnam(const char *__name)
{
	struct passwd *n = malloc(sizeof(struct passwd));
	n->pw_name = __name == NULL ? NULL : strdup(__name);
	n->pw_uid = 1024;
	n->pw_gid = 2048;
	n->pw_dir = "/home/c00clupea";
	n->pw_shell = "ash";
	return n;
}

