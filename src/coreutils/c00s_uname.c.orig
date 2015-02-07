/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	c00s_uname.c
 * created: 	Sun Aug 31 18:35:56 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
/* vi: set sw=4 ts=4: */
/* uname -- print system information
 * Copyright (C) 1989-1999 Free Software Foundation, Inc.
 *
 * Licensed under GPLv2 or later, see file LICENSE in this source tree.
 */

/* BB_AUDIT SUSv3 compliant */
/* http://www.opengroup.org/onlinepubs/007904975/utilities/uname.html */


#include "c00s_uname.h"

int UNAME_MAIN(int UNUSED(argc), char *argv[]){
	uname_info_t uname_info;
	const char *unknown_str = "unknown";
	const char *fmt;
	const unsigned short *delta;
	unsigned toprint;
	toprint = getopt32(argv,options);
	if (argv[optind]) { /* coreutils-6.9 compat */
		//bb_show_usage();
		printf("usage: uname [-amnrspv]");
	}
	if (toprint & (1 << 8)) { /* -a => all opts on */
		toprint = (1 << 8) - 1;
		unknown_str = ""; /* -a does not print unknown fields */
	}
	if (toprint == 0) { /* no opts => -s (sysname) */
		toprint = 1;
	}
	char path[PATH_MAX];
	FILE *fp;

	c00_util_create_config_path(path,"c00s_uname");

	fp = fopen(path,"r");
	check(fp,"File %s not exists",path);

	char line[1025];


	strcpy(uname_info.processor, unknown_str);
	strcpy(uname_info.platform, unknown_str);
	strcpy(uname_info.os, "GNU/Linux");
	delta = utsname_offset;

	int i = 0;
	int len;
	while(fgets(line,sizeof(line),fp) != NULL && i < 5){
		len = strlen(line);
		if(line[len - 1] == '\n'){
			line[len-1] = '\0';
		}
		char *p = (char *)(&uname_info)+delta[i];
		/**###########################
		 * This is real mess...solve it
		 **###########################
		 *  buffer problems when config too long
		 * <*))><
		 */
		strcpy(p,line);
		i++;
	}

	fclose(fp);
	fmt = " %s" + 1;

	do {
		if (toprint & 1) {
			const char *p = (char *)(&uname_info) + *delta;
			if (p[0]) {
				printf(fmt, p);
				fmt = " %s";
			}
		}
		++delta;
	} while (toprint >>= 1);
	printf("\n");
	return TRUE;


error:
	return ERROR;
}
