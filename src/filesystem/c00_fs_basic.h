/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	c00_fs_basic.h
 * created: 	Thu Sep 11 10:53:08 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */

#ifndef _C00_FS_BASIC_H_
#define _C00_FS_BASIC_H_
#include "../global.h"
#include <stdio.h>

#define _FS_CONTAINER_TYPE int
#define int

int c00_fs_mknod(_FS_CONTAINER_TYPE container, char *path, int mode);
int c00_fs_dlnod(_FS_CONTAINER_TYPE conatiner, char *path);
int c00_fs_open(_FS_CONTAINER_TYPE container, char *f, int mode);
int c00_fs_close(int handle);
int c00_fs_write(int handle, char val);
char c00_fs_read(int handle);
int c00_fs_seek(int handle, int seek);
/**some convenience**/
int c00_fs_seek_to_start(int handle);



#endif /* _C00_FS_BASIC_H_ */
