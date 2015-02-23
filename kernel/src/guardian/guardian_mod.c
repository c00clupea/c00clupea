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
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christoph Pohl");
MODULE_DESCRIPTION("C00clupea guardian");



#if ARCHDETECTED == X86_64
unsigned long *ia32_syscalltable;
#endif
unsigned long *syscalltable;


/*Some code from https://github.com/mncoppola/suterusu/blob/master/main.c*/
struct {
  unsigned short limit;
  unsigned long base;
} __attribute__ ((packed))idtr;
struct {
  unsigned short off1;
  unsigned short sel;
  unsigned char none, flags;
  unsigned short off2;
} __attribute__ ((packed))idt;



asmlinkage long (*org_sys_write)(unsigned int, const char __user* , size_t);
asmlinkage long (*org_sys_read)(unsigned int, char __user*, size_t);
asmlinkage int (*org_sys_open)(const char*, int, int);

asmlinkage int (*hook_sys_open)(const char*, int, int);



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

  __asm__ volatile("sidt %0":"=m"(idtr));
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


/*see http://badishi.com/kernel-writing-to-read-only-memory/*/
static inline int disable_write_protection(void){
  unsigned long b;
  __asm__ volatile("mov %%cr0, %0" : "=r" (b));
  __asm__ volatile("mov %0, %%cr0" : : "r" (b & ~P_FLAG));
  C00TRACE("Disable Write Protection\n");
  return TRUE;
}

static inline int enable_write_protection(void){
  unsigned long b;
  __asm__ volatile("mov %%cr0, %0" : "=r" (b));
  __asm__ volatile("mov %0, %%cr0" : : "r" (b | P_FLAG));
  C00TRACE("Enable Write Protection\n");
  return TRUE;
}




static int store_syscall_ptr(void)
{
  org_sys_read = (void *)syscalltable[__NR_read];
  org_sys_write = (void *)syscalltable[__NR_write];
  org_sys_open = (void *)syscalltable[__NR_open];

  hook_sys_open = &concrete_hook_sys_open;
  
  C00TRACE("read at %p\n",org_sys_read);
  C00TRACE("write at %p\n",org_sys_write);
  C00TRACE("open at %p\n",org_sys_open);
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
  printk("Address of hook open %p\n",hook_sys_open);
  printk("Address of hook open %p\n",&hook_sys_open);
  syscalltable[__NR_open] = hook_sys_open;
  enable_write_protection();
  
  return 0;   
}

static void __exit guardian_cleanup(void)
{
  disable_write_protection();
  syscalltable[__NR_open] = org_sys_open;
  enable_write_protection();
  
  C00TRACE("Cleaning up guardian_mod.\n");
}


module_init(guardian_init);
module_exit(guardian_cleanup);
