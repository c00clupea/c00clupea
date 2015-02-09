/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 * 
 * File:	c00s_hm_api.h
 * created: 	Mon Feb  9 07:40:44 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#ifndef C00S_HM_API_H
#define C00S_HM_API_H

#include "include/c00s_libcu.h"
#include <pwd.h>


/*User pwd and more user staff*/
int c00h_actualuser(struct passwd *pw);
int c00h_actualpwd(char *pwd);
int c00h_userbyname(struct passwd *pw, char *name);
int c00h_changepassword(uid_t uid, char *newp);



#endif /* C00S_HM_API_H */
