/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	interpreter.h
 * created: 	Wed Mar 25 10:26:39 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

#define _TEST_SUITE_

#ifdef _NOMOD_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#define ap_malloc(x,y) malloc(x)
#define GFP_KERNEL 0
#define as_free(x) free(x)
#define ap_print(x,...) printf(x,__VA_ARGS__)

#else

#define ap_print(x,...) printk(x__VA_ARGS__)
#define ap_malloc(x,y) kmalloc(x,y)
#define as_free(x) kfree(x)
#endif

#define as_malloc(x) ap_malloc(x,GFP_KERNEL)

#define CW_HELLO 0x001
#define CW_GOODBYE 0x002
#define CW_JMP 0x003
#define CW_RET 0x004
#define CW_CALLPTR 0x005

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


#define ERR_OOB 0x001,"Index out of range"
#define PRINTERR_FN(a,b) ap_print("ERROR: 0x%.8X %s \n",a,b);	\
  print_opcode(b->opcode_frame,remline)


#define PRINTERR(a) PRINTERR_FN(a)




struct ap_command_s{
  unsigned char cmd;
  union datatype_u dst;
  union datatype_u src;
};

struct ap_dword_s{
  unsigned char type;
  
  void *dst;
};

struct ap_data_s{
  struct ap_dword_s *data;
  unsigned long datalen;
};

struct ap_opcode_s{
  struct ap_command_s *stack;
  unsigned long stacklen;
};

struct ap_bytecode_s{
  struct ap_data_s *data_frame;
  struct ap_opcode_s *opcode_frame;
};

#ifdef __TEST_SUITE_
extern struct ap_command_s *sample_stack;
#endif

#define GEN_DATA_ADD_FN_NAME(x) int ap_data_add_ ## x (struct ap_data_s *d, int idx, x val)
#define GEN_DATA_ADD_FN_NAMEL(x,y) int ap_data_add_ ## x (struct ap_data_s *d, int idx, y val)

#define GEN_OPCODE_ADD_CMD(a,b) int ap_opcode_ ## a (struct ap_opcode_s *o, int idx, b val);

#define GEN_OPCODE_ADD_SCMD(a) int ap_opcode_ ## a (struct ap_opcode_s *o, int idx);

#define GEN_OPCODE_ADD_CMD_B(a,b,c) int ap_opcode_ ## a (struct ap_opcode_s *o, int idx, b dst, c src);

#define GEN_OPCODE_ADD_OC_FUNC(a,b) int ap_opcode_ ## a(struct ap_opcode_s *o, int idx){ \
  o->stack[idx].cmd = b;\
  o->stack[idx].src.dw_ptr = NULL;	\
  o->stack[idx].dst.dw_ptr = NULL;	\
  return 0;					\
  }


#define GEN_OPCODE_ADD_OC_FUNC_SRC(a,b,c,d) int ap_opcode_ ## a(struct ap_opcode_s *o, int idx, c val){ \
  o->stack[idx].cmd = b;\
  o->stack[idx].src.d = val;	\
  o->stack[idx].dst.dw_ptr = NULL;	\
  return 0;					\
  }

#define GEN_OPCODE_ADD_OC_FUNC_DST(a,b,c,d) int ap_opcode_ ## a(struct ap_opcode_s *o, int idx, c val){ \
  o->stack[idx].cmd = b;\
  o->stack[idx].dst.d = val;	\
  o->stack[idx].src.dw_ptr = NULL;	\
  return 0;				   \
  }

#define GEN_OPCODE_ADD_OC_FUNC_B(a,b,c,d,e,f) int ap_opcode_ ## a(struct ap_opcode_s *o, int idx, c dst, d src){ \
  o->stack[idx].cmd = b;\
  o->stack[idx].dst.e = dst;	\
  o->stack[idx].src.f = src;	\
  return 0;	\
  }

#define GEN_DATA_ADD_FN_FUNC(x,y) inline int ap_data_add_ ## x (struct ap_data_s *d, int idx, x val){ \
  if(idx < 0 || idx >= d->datalen){\
    return 1;			   \
}\
  d->data[idx].type = y ; \
  d->data[idx].dst = as_malloc(sizeof(x)); \
  memcpy(d->data[idx].dst,&val,sizeof(x)); \
  return 0;\
  }

#define GEN_DATA_ADD_FN_FUNCL(x,y,z) inline int ap_data_add_ ## x (struct ap_data_s *d, int idx, y val){ \
  d->data[idx].type = z ; \
  d->data[idx].dst = as_malloc(sizeof(y)); \
  memcpy(d->data[idx].dst,&val,sizeof(y)); \
  }

#define GEN_DATA_FN_FUNC(x,y) GEN_DATA_ADD_FN_FUNC(x,y)
#define GEN_DATA_FN_FUNCL(x,y,z) GEN_DATA_ADD_FN_FUNCL(x,y,z)
  
#define GEN_OPCODE_FUNC(a,b) GEN_OPCODE_ADD_OC_FUNC(a,b)
#define GEN_OPCODE_DST_FUNC(a,b,c,d) GEN_OPCODE_ADD_OC_FUNC_DST(a,b,c,d)
#define GEN_OPCODE_SRC_FUNC(a,b,c,d) GEN_OPCODE_ADD_OC_FUNC_SRC(a,b,c,d)
#define GEN_OPCODE_B_FUNC(a,b,c,d,e,f) GEN_OPCODE_ADD_OC_FUNC_B(a,b,c,d,e,f)
  
#define GEN_CASE_TYPE_F(a,t,c) case a:		\
  ap_print("idx %d: "#t"->%"#c"\n",i,*((t*)d->data[i].dst));\
  break

#define GEN_PRINT(a,t,c) GEN_CASE_TYPE_F(a,t,c)

#define GEN_CASE_OP_TYPE_F1(a) case a:		\
  ap_print("idx %05d:%-14s->%10s%10s\n",i,#a,"NULL","NULL");	\
  break

#define GEN_CASE_OP_TYPE_F2_DST(a,b,c) case a:\
  ap_print("idx %05d:%-14s->%10"#c"%10s\n",i,#a,o->stack[i].dst.b,"NULL");	\
  break

#define GEN_CASE_OP_TYPE_F2_SRC(a,b,c) case a:\
  ap_print("idx %05d:%-14s->%10s%10"#c"\n",i,#a,"NULL",o->stack[i].src.b);	\
  break
  
#define GEN_CASE_OP_TYPE_F3(a,b,c,d,e) case a:				\
  ap_print("idx %05d:%-14s->%10"#d"%10"#e"\n",i,#a,o->stack[i].dst.b,o->stack[i].src.c);	\
  break

#define OOB_PROTECTION \
  if(idx >= b->opcode_frame->stacklen){\
    PRINTERR(ERR_OOB);\
    goto error;\
}
  
int ap_data_add_chars(struct ap_data_s *d, int idx, char *val,int len);

int ap_data_add_NULL(struct ap_data_s *d, int idx);

//ap_data_add_char(struct ap_data_s *d, int idx, char val)
GEN_DATA_ADD_FN_NAME(char);
//ap_data_add_int(struct ap_data_s *d, int idx, int val)
GEN_DATA_ADD_FN_NAME(int);
//ap_data_add_short(struct ap_data_s *d, int idx, short val)
GEN_DATA_ADD_FN_NAME(short);
//ap_data_add_long(struct ap_data_s *d, int idx, long val)
GEN_DATA_ADD_FN_NAME(long);
//ap_data_add_float(struct ap_data_s *d, int idx, float val)
GEN_DATA_ADD_FN_NAME(float);
//ap_data_add_double(struct ap_data_s *d, int idx, double val)
GEN_DATA_ADD_FN_NAME(double);
//ap_data_add_double(struct ap_data_s *d, int idx, double val)
GEN_DATA_ADD_FN_NAMEL(long_double,long double);


GEN_DATA_ADD_FN_NAMEL(unsigned_char,unsigned char);
GEN_DATA_ADD_FN_NAMEL(unsigned_short,unsigned short);
GEN_DATA_ADD_FN_NAMEL(unsigned_int,unsigned int);
GEN_DATA_ADD_FN_NAMEL(unsigned_long,unsigned long);

GEN_OPCODE_ADD_SCMD(hello);
GEN_OPCODE_ADD_SCMD(goodbye);
GEN_OPCODE_ADD_CMD(jmp,int);
GEN_OPCODE_ADD_CMD(ret,int);
GEN_OPCODE_ADD_CMD(call,int);


 
int destroy_data_frame(struct ap_data_s *d);
struct ap_data_s *create_data_section(int len);
struct ap_opcode_s *create_opcode_section(int len);
int run_system(struct ap_bytecode_s *b);

#endif /* _INTERPRETER_H_ */
