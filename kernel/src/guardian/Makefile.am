SUFFIXES = .c .h .y .l
ACLOCAL_AMFLAGS = -I m4

AM_CPPFLAGS = 

AM_CFLAGS =  -std=gnu99 -Wall -Wextra -pedantic -D_THREAD_SAFE

AM_YFLAGS = -d #this is for yacc

BUILT_SOURCES =

if NEEDPTHREAD
AM_CFLAGS += -pthread
endif

if CLANG
AM_CFLAGS += -Wno-extended-offsetof
endif


EXTRA_PROGRAMS = guardian_mod

guardian_mod_SOURCES = guardian_mod.c
module_DATA = guardian_mod.o
include ../../Makefile.common

bin_PROGRAMS =

if C00WITHGUARDIAN
bin_PROGRAMS += guardianl
endif

if C00WITHGUARDIAN
BUILT_SOURCES += guardian_bison.h
guardianl_SOURCES = guardian.h guardian.c guardian_bison.y guardian_flex.l
endif



