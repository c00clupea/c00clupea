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
//#include "guardian_module.h"

#include "interpreter.h"

int interpretline(int *idx, char *commands)
{
  char cmd = commands[*idx];
  switch(cmd){
  case 0x001:
    //jmp <int> 
    break;
  case 0x002:
   //ret <>
    break;
  case 0x003:
    //call <ptr>
    break;
  case 0x004:
    //call <register>
    break;
  }
    
}

#ifdef _NOMOD_



int create_test_header(FILE *fp)
{
  struct binheader *bin_header_t =  malloc(sizeof(struct binheader));
  strncpy(bin_header_t->type,"apatebytecode",13);
  bin_header_t->headerlen=sizeof(struct binheader);
  fwrite(bin_header_t,sizeof(struct binheader),1,fp);
  free(bin_header_t);
  return 1;
}

int write_command_two_int(FILE *fp, char cmd, int val1, int val2)
{
  fwrite(&cmd,sizeof(char),1,fp);
  fwrite(&val2,sizeof(int),1,fp);
  fwrite(&val1,sizeof(int),1,fp);
  return 1;
}

int add_charconstant(char *ident, char *value){
  return 1;
}

int disassemble(char *filename)
{
  FILE *fp = fopen(filename,"rb");
  struct binheader thisheader;
  fread(&thisheader,sizeof(struct binheader),1,fp);
  printf("Type %s\n",thisheader.type);
  printf("Headerlen %d\n",thisheader.headerlen);
  
  fclose(fp);
}

int main(int argc, char *argv)
{
  FILE *fp;
  fp = fopen("testbytecode/simpletest.ba","wb");
  create_test_header(fp);
  
  write_command_two_int(fp,CMD_JMP,42,82);
  fflush(fp);
  fclose(fp);
  disassemble("testbytecode/simpletest.ba");
}
#endif
