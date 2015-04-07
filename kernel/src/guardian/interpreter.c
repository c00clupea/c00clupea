/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	interpreter.c
 * created: 	Wed Mar 25 10:24:03 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#ifndef _NOMOD_
#include "guardian_module.h"
#endif

#include "interpreter.h"

#ifdef _NOMOD_
#ifdef _TEST_SUITE_


#endif
#endif

static int print_dataframe(struct ap_data_s *d)
{
for(long i = 0; i < d->datalen;i++){
      switch(d->data[i].type){
      case DW_CHAR_PTR:
	ap_print("idx %d: *char-> %s\n",i,d->data[i].dst);
	break;
      case DW_NIL:
	ap_print("idx %d: NIL-> NULL\n",i);	
	break;
	GEN_PRINT(DW_CHAR,char,c);
	GEN_PRINT(DW_SHORT,short,d);
	GEN_PRINT(DW_INT,int,d);
	GEN_PRINT(DW_LONG,long,ld);
	GEN_PRINT(DW_UCHAR,unsigned char,c);
	GEN_PRINT(DW_USHORT,unsigned short,d);
	GEN_PRINT(DW_UINT,unsigned int,d);
	GEN_PRINT(DW_ULONG,unsigned long,ld);
	GEN_PRINT(DW_FLOAT,float,f);
	GEN_PRINT(DW_DOUBLE,double,lf);
	GEN_PRINT(DW_LDOUBLE,long double,LF);
      default:
	ap_print("idx %d: Type unknown-> NIL\n",i);
	break;
      }
 }
}

static int print_opcode(struct ap_opcode_s *o,long i)
{
    switch(o->stack[i].cmd){
    GEN_CASE_OP_TYPE_F1(CW_HELLO);
    GEN_CASE_OP_TYPE_F1(CW_GOODBYE);
    GEN_CASE_OP_TYPE_F2_DST(CW_JMP,dw_int,d);
    default:
      ap_print("idx %05d:%-14s->%10s%10s\n",i,"NOP","NULL","NULL");
      break;
    }
    return 0;
}

static int print_opcodeframe(struct ap_opcode_s *o)
{
  for(long i = 0; i < o->stacklen; i++){
    print_opcode(o,i);
  }
  return 0;
}
 
static int print_bytecode(struct ap_bytecode_s *b)
{
  if(!b){
    goto error;
  }
  if(b->data_frame){
    print_dataframe(b->data_frame);
  }
  else{
    goto error;
  }
  if(b->opcode_frame){
    print_opcodeframe(b->opcode_frame);
  }
  else{
    goto error;
  }
  return 1;
 error:
  ap_print("error with %d\n",0);
  return 0;
}

GEN_DATA_FN_FUNC(char,DW_CHAR);
GEN_DATA_FN_FUNC(short,DW_SHORT);
GEN_DATA_FN_FUNC(int,DW_INT);
GEN_DATA_FN_FUNC(long,DW_LONG);
GEN_DATA_FN_FUNC(float,DW_FLOAT);
GEN_DATA_FN_FUNC(double,DW_DOUBLE);
GEN_DATA_FN_FUNCL(long_double,long double,DW_LDOUBLE);

GEN_DATA_FN_FUNCL(unsigned_char,unsigned char,DW_UCHAR);
GEN_DATA_FN_FUNCL(unsigned_short,unsigned short,DW_USHORT);
GEN_DATA_FN_FUNCL(unsigned_int,unsigned int,DW_UINT);
GEN_DATA_FN_FUNCL(unsigned_long,unsigned long,DW_ULONG);

GEN_OPCODE_FUNC(hello,CW_HELLO);
GEN_OPCODE_FUNC(goodbye,CW_GOODBYE);
GEN_OPCODE_DST_FUNC(jmp,CW_JMP,int,dw_int);

inline int ap_data_add_chars(struct ap_data_s *d, int idx, char *val,int len){
  if(idx < 0 || idx >= d->datalen){
    return 1;
  }
  d->data[idx].type = DW_CHAR_PTR;
  d->data[idx].dst = (void *)as_malloc(len);
  strncpy(d->data[idx].dst,val,len-1);
  return 0;
}

inline int ap_data_add_NULL(struct ap_data_s *d, int idx)
{
    if(idx < 0 || idx >= d->datalen){
    return 1;
  }
  d->data[idx].type = DW_NIL;
  d->data[idx].dst = NULL;
  return 0;
}

int destroy_data_frame(struct ap_data_s *d){
  if(d != NULL){
    long c = 0;
    for(c= 0; c < d->datalen;c++){
      as_free(d->data[c].dst);

    }
    as_free(d->data);
    as_free(d);
  }
}

inline struct ap_data_s *create_data_section(int len)
{
  struct ap_data_s *d = as_malloc(sizeof(struct ap_data_s));
  d->data = as_malloc(len * sizeof(struct ap_dword_s));
  d->datalen = len;
  return d;
}

inline struct ap_opcode_s *create_opcode_section(int len)
{
  struct ap_opcode_s *o = as_malloc(sizeof(struct ap_opcode_s));
  o->stack = as_malloc(len * sizeof(struct ap_command_s));
  o->stacklen = len;
  return o;
}



inline int run_system(struct ap_bytecode_s *b)
{
  long idx = 0;
  long remline = 0;
  while(1){
   switch(b->opcode_frame->stack[idx].cmd){
   case CW_HELLO:
    remline = idx;
    idx++;
    OOB_PROTECTION;
    break;
   case CW_JMP:
     remline = idx;
     idx = b->opcode_frame->stack[idx].dst.dw_int;
     OOB_PROTECTION;
     break;
   case CW_GOODBYE:
    remline = idx;
    goto breakout;
    break;
  default:
    remline = idx;
    idx++;
    OOB_PROTECTION;
    break;
  }

  }
 breakout:
  ap_print("Goodbye at %d\n",remline);
    return 0;
 error:
    ap_print("System exited with error %-10d\n",remline);
    return 1;
}

#ifdef _NOMOD_
#ifdef _TEST_SUITE_

static int fill_test_data_section(struct ap_data_s *d)
{
  ap_data_add_chars(d,0,"Hallo",6);
  ap_data_add_char(d,1,'a');
  ap_data_add_int(d,2,42);
  ap_data_add_short(d,10,42);
  ap_data_add_long(d,3,424242);
  ap_data_add_float(d,4,42.42);
  ap_data_add_double(d,5,4243);
  ap_data_add_long_double(d,6,4243);
  
  ap_data_add_unsigned_char(d,7,'b');
  ap_data_add_unsigned_int(d,8,42);
  ap_data_add_unsigned_long(d,9,424242);
  ap_data_add_unsigned_short(d,11,43);
  ap_data_add_NULL(d,12);

  
}

static int fill_test_opcode_section(struct ap_opcode_s *o)
{
  ap_opcode_hello(o,0);
  ap_opcode_goodbye(o,39);
  ap_opcode_jmp(o,1,38);
}

static struct ap_data_s *init_test_data_section(){
  struct ap_data_s *d = create_data_section(13);
  fill_test_data_section(d);
  return d;
}

static struct ap_opcode_s *init_test_opcode_section(){
  struct ap_opcode_s *o = create_opcode_section(40);
  fill_test_opcode_section(o);
  return o;
}

static struct ap_bytecode_s *init_test_bytecode()
{
  struct ap_bytecode_s *b = as_malloc(sizeof(struct ap_bytecode_s));
  b->data_frame = init_test_data_section();
  b->opcode_frame = init_test_opcode_section();
  print_bytecode(b);
  return b;
}

static int destroy_test_bytecode(struct ap_bytecode_s *bytecode)
{
  destroy_data_frame(bytecode->data_frame);
  as_free(bytecode->opcode_frame);
  as_free(bytecode);
}


int main(int argc, char *argv)
{
  struct ap_bytecode_s *b = init_test_bytecode();
  run_system(b);
  destroy_test_bytecode(b);
  
}
#endif
#endif
