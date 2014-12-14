/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 * 
 * File:	c00_message.c
 * created: 	Mon Dec  8 06:37:50 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#include "c00_message.h"

int c00_connect_honeymaster(struct c00_ident *id){
	mem_check(id)
	return TRUE;
error:
	return ERROR;
}
int c00_close_honeymaster(struct c00_ident *id){
	mem_check(id)
	return TRUE;
error:
	return ERROR;
}
int c00_open_internalfile(struct c00_msg *msg, FILE *fd){
	mem_check(msg)
	return TRUE;
error:
	return ERROR;
}
int c00_close_internalfile(struct c00_ident *id, FILE *fd){
	return TRUE;
}
