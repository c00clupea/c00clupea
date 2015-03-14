/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	rules.c
 * created: 	Sat Mar 14 15:15:57 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#include "guardian_module.h"
/*
*Borrowed from hackers delight 2.ed*
static inline int nlz(unsigned x) {
   int n;

   if (x == 0) return(32);
   n = 0;
   if (x <= 0x0000FFFF) {n = n +16; x = x <<16;}
   if (x <= 0x00FFFFFF) {n = n + 8; x = x << 8;}
   if (x <= 0x0FFFFFFF) {n = n + 4; x = x << 4;}
   if (x <= 0x3FFFFFFF) {n = n + 2; x = x << 2;}
   if (x <= 0x7FFFFFFF) {n = n + 1;}
   return n;
}
*Also from hackers delight..pretty cool*
static inline int c00_zbytel(unsigned x)
{
   unsigned y;
   int n;
   y = (x & 0x7F7F7F7F) + 0x7F7F7F7F; 
   y = ~(y | x | 0x7F7F7F7F);         
   n = nlz(y) >> 3;            
   return n;                   
}

inline int c00_fst_strlen(const char *buf)
{
  int someword;
  const int *someword_ptr;
  int c = 0;
  int r;
  someword_ptr = (int *)buf;

  for(;;){
    someword = *someword_ptr++;
    r = c00_zbytel(someword);
    c += r;
    if(r != 4){
      return c;
    }
  }
}
*/
inline int cond_eq_int(int a, int b)
{
  if(a == b){
    return TRUE;
  }
  return FALSE;
}

inline int cond_eq_str(const char *a, const char *b)
{
  /*just a fast check for null ways better than strlen*/
  if(*a == '\0' || *b == '\0'){
      return FALSE;
  }

  /*One more instruction, but a chance to avoid many instructions doing strcmp*/
  if(*a != *b){
    return FALSE;
  }
  if(strcmp(a,b) == 0){
    return TRUE;
  }
  return FALSE;
}
