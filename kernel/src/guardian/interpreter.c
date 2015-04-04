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

static int print_bytecode(struct ap_bytecode_s *b)
{
  if(!b){
    goto error;
  }
  if(b->data_frame){
    for(long i = 0; i < b->data_frame->datalen;i++){
      switch(b->data_frame->data[i].type){
      case DW_CHAR_PTR:
	ap_print("idx %d: *char-> %s\n",i,b->data_frame->data[i].dst);
	break;
      case DW_CHAR:
	ap_print("idx %d: char-> %s\n",i,b->data_frame->data[i].dst);
	break;
      case DW_INT:
	ap_print("idx %d: int-> %d\n",i,*((int*)b->data_frame->data[i].dst));
	break;
      case DW_LONG:
	ap_print("idx %d: long-> %ld\n",i,*((long*)b->data_frame->data[i].dst));
	break;
      case DW_FLOAT:
	ap_print("idx %d: float-> %f\n",i,*((float*)b->data_frame->data[i].dst));
	break;
      default:
	ap_print("idx %d: Type unknown-> NIL\n",i);
	break;
      }
    }
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
GEN_DATA_FN_FUNC(int,DW_INT);
GEN_DATA_FN_FUNC(long,DW_LONG);
GEN_DATA_FN_FUNC(float,DW_FLOAT);
int ap_data_add_chars(struct ap_data_s *d, int idx, char *val,int len){
  d->data[idx].type = DW_CHAR_PTR;
  d->data[idx].dst = (void *)as_malloc(len);
  strncpy(d->data[idx].dst,val,len-1);
}


#ifdef _NOMOD_
#ifdef _TEST_SUITE_

static int fill_test_data_section(struct ap_data_s *d)
{
  ap_data_add_chars(d,0,"Hallo",6);
  ap_data_add_char(d,1,'h');
  ap_data_add_int(d,2,42);
  ap_data_add_long(d,3,424242);
  ap_data_add_float(d,4,42.42);

  
  for(int i = 5; i <10;i++){
    d->data[i].type = DW_NIL;
    d->data[i].dst = NULL;
  }
}

static struct ap_data_s *init_test_data_section(){
  struct ap_data_s *d = as_malloc(sizeof(struct ap_data_s));
  d->data = malloc(10 * sizeof(struct ap_dword_s));
  d->datalen = 10;
  fill_test_data_section(d);
  return d;
}

static struct ap_opcode_s *init_test_opcode_section(){
  struct ap_opcode_s *o = as_malloc(sizeof(struct ap_opcode_s));
  o->stack = as_malloc(40 * sizeof(struct ap_command_s));
  o->stacklen = 40;
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
  
  as_free(bytecode->data_frame);
  as_free(bytecode->opcode_frame);
  as_free(bytecode);
}


int main(int argc, char *argv)
{
  struct ap_bytecode_s *b = init_test_bytecode();

  destroy_test_bytecode(b);
  
}
#endif
#endif
