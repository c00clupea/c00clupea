/* vi: set sw=4 ts=4: */
/* Copyright (C) 1991,92,95,96,97,98,99,2001 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

/*
 * POSIX Standard: 9.2.2 User Database Access	<pwd.h>
 */

#ifndef BB_PWD_H
#define BB_PWD_H 1
/*#include "../util/busybox_cccc.h"*/
#include <stdlib.h>
#include <pwd.h>
#include <string.h>


/* This file is #included after #include <pwd.h>
 * We will use libc-defined structures, but will #define function names
 * so that function calls are directed to bb_internal_XXX replacements
 */
#undef endpwent
/*
#define setpwent    bb_internal_setpwent
#define endpwent    bb_internal_endpwent
#define getpwent    bb_internal_getpwent
#define fgetpwent   bb_internal_fgetpwent
#define putpwent    bb_internal_putpwent
#define getpwuid    bb_internal_getpwuid

#define getpwent_r  bb_internal_getpwent_r
#define getpwuid_r  bb_internal_getpwuid_r
#define getpwnam_r  bb_internal_getpwnam_r
#define fgetpwent_r bb_internal_fgetpwent_r
*/
#define getpwnam    bb_internal_getpwnam

extern struct passwd *getpwnam(const char *__name);





#endif
