/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 * 
 * File:	guardian_mod.c
 * created: 	Sun Feb 22 21:05:56 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#include "guardian_module.h"

#define MODULE_NAME "c00clupeaguardian"
#if ARCHDETECTED == X86_64
unsigned long *ia32_syscalltable;
#endif
unsigned long *syscalltable;

asmlinkage long (*org_sys_write)(unsigned int fd, const char __user *buf, size_t count);
asmlinkage long (*org_sys_read)(unsigned int fd, char __user *buf, size_t count);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christoph Pohl");
MODULE_DESCRIPTION("C00clupea guardian");


/*Borrowed from https://github.com/mncoppola/suterusu/blob/master/util.c*/
void *memmem ( const void *haystack, size_t haystack_size, const void *needle, size_t needle_size )
{
  char *p;

  for ( p = (char *)haystack; p <= ((char *)haystack - needle_size + haystack_size); p++ )
    if ( memcmp(p, needle, needle_size) == 0 )
      return (void *)p;

  return NULL;
}


#if ARCHDETECTED == X86_64
/*Idea from http://www.exploit-db.com/papers/13146/*/
/*And from http://phrack.org/archives/issues/58/7.txt*/
unsigned long *obtain_ia32_syscalltable(void) {
  unsigned long res_offset = 0;
  unsigned char c[512];
  char **p;

  asm("sidt %0":"=m"(idtr));
  memcpy(&idt, (void *)(idtr.base + 16 * 0x80), sizeof(idt));
  res_offset = (idt.off2 << 16) | idt.off1;
  memcpy(c, (void *)res_offset, sizeof(c));
  p = (char **)memmem(c, sizeof(c), "\xff\x14\xc5", 3);

  if (p)
    {
      unsigned long *res = *(unsigned long **)((char *)p +3);
      res = (unsigned long *)(((unsigned long)res & 0xffffffff) | 0xffffffff00000000);
      return res;
    }
  else
    {
      return NULL;
    }
  
}

unsigned long *obtain_syscalltable(void) {
  unsigned long res_offset = 0;
  unsigned char c[512];
  char **p;

  rdmsrl(MSR_LSTAR, res_offset);
  memcpy(c, (void *)res_offset, sizeof(c));

  p = (char **)memmem(c, sizeof(c), "\xff\x14\xc5", 3);

  if (p)
    {
      unsigned long *res = *(unsigned long **)((char *)p +3);
      res = (unsigned long *)(((unsigned long)res & 0xffffffff) | 0xffffffff00000000);
      return res;
    }
  else
    {
      return NULL;
    }

}
#endif

#if ARCHDETECTED == I386
/*See http://phrack.org/archives/issues/58/7.txt*/
unsigned long *obtain_syscalltable(void)
{
  unsigned long res_offset = 0;
  unsigned char c[255];
  char **p;

  asm("sidt %0":"=m"(idtr));
  memcpy(&idt, (void *)(idtr.base + 8 * 0x80), sizeof(idt));  
  res_offset = (idt.off2 << 16) | idt.off1;
  memcpy(c, (void *)res_offset, sizeof(c));
  p = (char **)memmem(c, sizeof(c), "\xff\x14\x85", 3);
  if(p)
    {
      return *(unsigned long **)((char *)p+3);
    }
  else {
    return NULL;
  }

}
#endif

static inline int disable_write_protection(void){
  unsigned long b;
  __asm__("mov %%cr0, %0" : "=r" (b));
  __asm__("mov %0, %%cr0" : : "r" (b | ~P_FLAG));
  return TRUE;
}

static inline int enable_write_protection(void){
  unsigned long b;
  __asm__("mov %%cr0, %0" : "=r" (b));
  __asm__("mov %0, %%cr0" : : "r" (b | P_FLAG));
  return TRUE;
}


static int store_syscall_ptr(void)
{
  org_sys_read = (void *)syscalltable[__NR_read];
  org_sys_write = (void *)syscalltable[__NR_write];

  C00TRACE("read at %p\n",org_sys_read);
  C00TRACE("write at %p\n",org_sys_write);
  return TRUE;
}

static int __init guardian_init(void)
{

#if ARCHDETECTED == X86_64
  ia32_syscalltable = obtain_ia32_syscalltable();
#endif
  syscalltable = obtain_syscalltable();
  C00TRACE("Starting guardian_mod!\n");

  C00TRACE("found syscall_table at %p\n",syscalltable);
#if ARCHDETECTED == X86_64
  C00TRACE("found syscall_table ia32 at %p\n",ia32_syscalltable);
#endif

  
  if(store_syscall_ptr() != TRUE){
    C00TRACE("Can not store syscall table");
    return 1;
  }
  disable_write_protection();
  enable_write_protection();
  
  return 0;   
}

static void __exit guardian_cleanup(void)
{

  C00TRACE("Cleaning up guardian_mod.\n");
}


module_init(guardian_init);
module_exit(guardian_cleanup);
