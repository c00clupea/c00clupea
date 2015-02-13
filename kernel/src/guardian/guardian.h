/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 * 
 * File:	apatebash.h
 * created: 	Sat Jan 31 15:59:37 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#ifndef APATEBASH_H
#define APATEBASH_H

#define TRUE 1
#define FALSE 0
#define ERROR -1
#include <stdio.h>


extern FILE *yyin;
int yyparse(void);
extern int sym[26];

int main(int argc, char *argv[]);

#endif /* APATEBASH_H */
