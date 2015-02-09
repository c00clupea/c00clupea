/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 * 
 * File:	c00s_touch.c
 * created: 	Mon Feb  9 10:11:32 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#include "coreutils/c00s_touch.h"

int TOUCH_MAIN(int argc, char *argv[]){
	int fd;
	int status = TRUE;
	unsigned opts;
	enum {
		OPT_c = (1 << 0),
	};


	
	opts = getopt32(argv, "c");

	argv += optind;

	if(!*argv) {
		C00STDOUTN("usage: [c]");
		return status;
	}
	do {
		int result;
		result = utimes(*argv,NULL);
		if(result != 0) {
			if (errno == ENOENT) {
				if (opts & OPT_c) {
					continue;
				}
				fd = open(*argv, O_RDWR | O_CREAT, 0666);
				if(fd >= 0){
					close(fd);
					continue;
				}
			}
		}
		status = ERROR;
		C00STDOUT("%s\n",*argv);
	} while(*++argv);
	return status;
}
