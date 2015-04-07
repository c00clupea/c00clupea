/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	gen_methods.h
 * created: 	Tue Apr  7 21:46:59 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#ifndef _GEN_METHODS_H_
#define _GEN_METHODS_H_


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

#define GEN_DATA_ADD_FN_FUNC(x,y,z) inline int ap_data_add_ ## x (struct ap_data_s *d, int idx, x val){ \
  if(idx < 0 || idx >= d->datalen){\
    return 1;			   \
}\
  d->data[idx].type = y ; \
  d->data[idx].dst.z = val; \
  return 0;\
  }

#define GEN_DATA_ADD_FN_FUNCL(x,y,z,a) inline int ap_data_add_ ## x (struct ap_data_s *d, int idx, y val){ \
  d->data[idx].type = z ; \
  d->data[idx].dst.a = val; \
  }

#define GEN_DATA_FN_FUNC(x,y,z) GEN_DATA_ADD_FN_FUNC(x,y,z)
#define GEN_DATA_FN_FUNCL(x,y,z,a) GEN_DATA_ADD_FN_FUNCL(x,y,z,a)
  
#define GEN_OPCODE_FUNC(a,b) GEN_OPCODE_ADD_OC_FUNC(a,b)
#define GEN_OPCODE_DST_FUNC(a,b,c,d) GEN_OPCODE_ADD_OC_FUNC_DST(a,b,c,d)
#define GEN_OPCODE_SRC_FUNC(a,b,c,d) GEN_OPCODE_ADD_OC_FUNC_SRC(a,b,c,d)
#define GEN_OPCODE_B_FUNC(a,b,c,d,e,f) GEN_OPCODE_ADD_OC_FUNC_B(a,b,c,d,e,f)
  
#define GEN_CASE_TYPE_F(a,t,c,x) case a:			\
  ap_print("idx %d: "#t"->%"#c"\n",i,d->data[i].dst.x);	\
  break

#define GEN_PRINT(a,t,c,x) GEN_CASE_TYPE_F(a,t,c,x)

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

#define PRINTERR_FN(a,c) ap_print("ERROR: 0x%.8X %s \n",a,c);	\
  print_opcode(b->opcode_frame,remline);


#define PRINTERR(a) PRINTERR_FN(a)



#endif /* _GEN_METHODS_H_ */
