/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 * 
 * File:	c00s_usleep.c
 * created: 	Thu Nov 27 06:27:17 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */

#include "c00s_usleep.h"

int USLEEP_MAIN(int UNUSED(argc), char *argv[]){

	if (!argv[1]) {
		printf("usage: usleep N\n");
	}
	long sleeping;

	if (c00_strtolpos(argv[1],&sleeping) != TRUE){
		return TRUE; //No problem, same behavior than original
	}
	usleep(sleeping);
#	printf("sleeping for %ld ms",sleeping);
	return TRUE;
}
