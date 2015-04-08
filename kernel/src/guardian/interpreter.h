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

#include "datatypes_def.h"

#define as_malloc(x) ap_malloc(x,GFP_KERNEL)

#define ERR_OOB 0x001,"Index out of range"

struct ap_command_s{
  unsigned char cmd;
  union datatype_u dst;
  union datatype_u src;
};

struct ap_dword_s{
  unsigned char type;
  union datatype_u dst;
  //  void *dst;
};

struct ap_register_s{
  unsigned int reglen;
  struct ap_dword_s reg[6];
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

#include "gen_methods.h"

#define OOB_PROTECTION \
  if(idx >= b->opcode_frame->stacklen){\
    PRINTERR(ERR_OOB);		  \
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
GEN_OPCODE_ADD_SCMD(nop);
GEN_OPCODE_ADD_SCMD(goodbye);
GEN_OPCODE_ADD_CMD(jmp,int);
GEN_OPCODE_ADD_CMD(ret,int);
GEN_OPCODE_ADD_CMD(call,int);


 
int destroy_data_frame(struct ap_data_s *d);
struct ap_data_s *create_data_section(int len);
struct ap_opcode_s *create_opcode_section(int len);
int run_system(struct ap_bytecode_s *b);

/*opcodes*/

INT_OC_OP_H(nop);
INT_OC_OP_H(hello);

#endif /* _INTERPRETER_H_ */
