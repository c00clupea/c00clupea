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

#define CMD_JMP 0x001
#define RET 0x002
#define CALLPTR 0x003

#define DW_CHAR_PTR 0x001
#define DW_CHAR 0x002
#define DW_INT 0x003
#define DW_LONG 0x004
#define DW_FLOAT 0x005
#define DW_NIL 0x006


struct ap_command_s{
  unsigned char cmd;
  void *dst;
  void *src;
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

#define GEN_DATA_ADD_FN_FUNC(x,y) int ap_data_add_ ## x (struct ap_data_s *d, int idx, x val){ \
  d->data[idx].type = y ; \
  d->data[idx].dst = as_malloc(sizeof(x)); \
  memcpy(d->data[idx].dst,&val,sizeof(x)); \
  }

#define GEN_DATA_FN_FUNC(x,y) GEN_DATA_ADD_FN_FUNC(x,y)

//ap_data_add_char(struct ap_data_s *d, int idx, char val)
GEN_DATA_ADD_FN_NAME(char);
//ap_data_add_int(struct ap_data_s *d, int idx, int val)
GEN_DATA_ADD_FN_NAME(int);
//ap_data_add_long(struct ap_data_s *d, int idx, long val)
GEN_DATA_ADD_FN_NAME(long);
//ap_data_add_float(struct ap_data_s *d, int idx, float val)
GEN_DATA_ADD_FN_NAME(float);





#endif /* _INTERPRETER_H_ */
