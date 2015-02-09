/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 * 
 * File:	c00s_pwd.c
 * created: 	Mon Feb  9 10:50:59 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#include "coreutils/c00s_pwd.h"

int PWD_MAIN(int argc, char *argv[])
{
	char *curdir;
	curdir = malloc(PATH_MAX*(sizeof(char)));

	check(c00h_actualpwd(curdir),"no dir readable%s","");

	C00STDOUT("%s\n",curdir);
error:
	return ERROR;
}
