/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 * 
 * File:	c00s_xatonum.c
 * created: 	Thu Nov 27 09:10:42 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#include "c00s_xatonum.h"

static inline int __in_range(long val,long min, long max);
static inline int __basic_strol(const char *args, long *val,long min,long max);


int __in_range(long val,long min, long max){
	if(val >= min && val <= max){
		return TRUE;
	}
	return FALSE;
}

int c00_strtoipos(const char *args, int *val){

	if(c00_strtoi(args, val) != TRUE){
		return FALSE;
	}

	if(__in_range(*val,0,INT_MAX) != TRUE){
		printf("error2");
		return FALSE;
	}
	return TRUE;
	
}

int c00_strtolpos(const char *args, long *val){

	if(c00_strtol(args, val) != TRUE){
		return FALSE;
	}

	if(__in_range(*val,0,INT_MAX) != TRUE){
		printf("error2");
		return FALSE;
	}
	return TRUE;
	
}

int __basic_strol(const char *args, long *val,long min, long max){
	check(args,"%s should not be null","args");
	char *end;
	*val = strtol(args,&end,10);

	if(end == args){
		*val = 0;
		//not dec
		return ERROR;
	}
	else if('\0' != *end){
		*val = 0;
		//something wrong in string
		return ERROR;
	}
	else if(!__in_range(*val,min,max)){
		*val = 0;
		//out of range
		return ERROR;
	}
	return TRUE;
error:
	return ERROR;
}

int c00_strtoi(const char *args, int *val){
	long v1;
	if(__basic_strol(args,&v1,INT_MIN,INT_MAX) != TRUE){
		*val = 0;
		return ERROR;
	}
	*val = (int)v1;

	return TRUE;
}

int c00_strtol(const char *args, long *val){
	long v1;
	if(__basic_strol(args,&v1,LONG_MIN,LONG_MAX) != TRUE){
		*val = 0;
		return ERROR;
	}
	*val = v1;

	return TRUE;
}