/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	datatypes_def.h
 * created: 	Tue Apr  7 21:44:12 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#ifndef _DATATYPES_DEF_H_
#define _DATATYPES_DEF_H_


#define CW_HELLO 0x001
#define CW_GOODBYE 0x002
#define CW_JMP 0x003
#define CW_RET 0x004
#define CW_CALLPTR 0x005





#define DW_CHAR_PTR 0x001
#define DW_CHAR 0x002
#define DW_SHORT 0x003
#define DW_INT 0x004
#define DW_LONG 0x005
#define DW_FLOAT 0x006
#define DW_DOUBLE 0x007
#define DW_LDOUBLE 0x008

//unsigned
#define DW_UCHAR 0x009
#define DW_USHORT 0x00A
#define DW_UINT 0x00B
#define DW_ULONG 0x00C

#define DW_NIL 0x00D

#define MUST_BE_FREED DW_CHAR_PTR,DW_FLOAT,DW_DOUBLE,DW_LDOUBLE
#define MUST_BE_FREED_LEN 4




//sorted by size
union datatype_u{
  char dw_char;
  unsigned char dw_uchar;
  short dw_short;
  unsigned short dw_ushort;
  int dw_int;
  unsigned int dw_uint;
  long dw_long;
  unsigned long dw_ulong;
  long long dw_longlong;
  unsigned long long dw_ulonglong;
  void * dw_ptr;
};


#endif /* _DATATYPES_DEF_H_ */
