/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 * 
 * File:	c00s_strings.c
 * created: 	Fri Nov 28 13:42:54 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#include "c00s_strings.h"


int STRINGS_MAIN(int UNUSED(argc), char *argv[]){
	unsigned n;
	int c;
	int status = TRUE;
	unsigned count;
	off_t offset;
	FILE *file;
	char *string;
	const char *fmt = "%s: ";
	const char *n_arg = "4";
	int sn;

	getopt32(argv,"afon:", &n_arg);

	argv += optind;
	if(c00_strtoi_in_range(n_arg,&sn,1,INT_MAX) != TRUE){
		printf("not in range");
		exit(1);
	}
	n = (unsigned)sn;
	string = xzalloc(n + 1);
	n--;
	if(!*argv){
		fmt = "{%s}: ";
		*--argv = (char *)bb_msg_standard_input;
	}
	do {
		file = fopen_or_warn_stdin(*argv);
		if(!file){
			status = ERROR;
			printf("strings: '%s': No such file\n",*argv);
			continue;
		}
		offset = 0;
		count = 0;
		do {
			c = fgetc(file);
			if(isprint_asciionly(c) || c == '\t'){
				if(count > n){
					putchar(c);
				}else{
					string[count] = c;
					if(count == n){
						if(option_mask32 & PRINT_NAME){
							printf(fmt, *argv);
						}
						if(option_mask32 & PRINT_OFFSET){
							printf("%7"OFF_FMT"o ",offset -n);
						}
						fputs(string,stdout);
					}
					count++;
				}
			}
			else {
				if (count > n){
					putchar('\n');
				}
				count = 0;
			}
			offset++;
		}while (c != EOF);
	}while (*++argv);

	free(string);

	return status;
}
