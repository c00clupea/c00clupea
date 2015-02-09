/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 * 
 * File:	c00s_hm_api.c
 * created: 	Mon Feb  9 07:47:35 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#include "include/c00s_hm_api.h"

int c00h_actualuser(struct passwd *pw)
{
	mem_check(pw);
	pw->pw_name = "c00clupea_fix";
	pw->pw_passwd = "hallowelt";
	pw->pw_uid = 4242;
	pw->pw_gid = 4243;
	pw->pw_dir = "/home/c00clupea";
	pw->pw_shell = "/usr/local/bin/c00nb-shell";
	return TRUE;

error:
	C00DEBUG("no user alloc%s","");
	return ERROR;
}


int c00h_userbyname(struct passwd *pw, char *name)
{
	mem_check(pw);
	mem_check(name);
	pw->pw_name = "c00clupea_other";
	pw->pw_passwd = "hallowelt";
	pw->pw_uid = 4245;
	pw->pw_gid = 4246;
	pw->pw_dir = "/home/c00clupea";
	pw->pw_shell = "/usr/local/bin/c00nb-shell";
	return TRUE;
error:
	C00DEBUG("no user alloc%s","");
	return ERROR;
}

int c00h_changepassword(uid_t uid, char *newp)
{
	return TRUE;
}
