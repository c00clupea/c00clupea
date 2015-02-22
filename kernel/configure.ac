AC_PREREQ([2.69])
AC_INIT([c00clupeakernel], [01], [christoph.pohl0@hm.edu])
#AC_CONFIG_SRCDIR([src/config.c])
#AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([subdir-objects])
# Checks for programs.

AC_PROG_CC(gcc)

AC_PROG_YACC
AC_PROG_LEX


# this is for automakes beyond 1.14
AM_PROG_CC_C_O

#AC_CHECK_HEADERS([stdio.h unistd.h stdlib.h time.h limits.h string.h pthread.h sys/wait.h])

AC_TYPE_SIZE_T

AC_FUNC_MALLOC

AC_CHECK_FUNCS([memset])
AC_CHECK_HEADERS([libintl.h])
AC_CHECK_HEADERS([malloc.h])
AC_CHECK_HEADERS([stddef.h])
AC_FUNC_ALLOCA
AC_FUNC_REALLOC
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT8_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

AC_PATH_KERNEL_SOURCE

AC_CONFIG_HEADERS([src/conf.h])

AC_CONFIG_FILES([Makefile src/guardian/Makefile])

AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([], [[
#ifndef __clang__
       not clang
#endif
]])],
[CLANG=yes], [CLANG=no])

AC_MSG_RESULT([$CLANG])

AC_CANONICAL_HOST

AM_CONDITIONAL([ISDARWIN],false)
AM_CONDITIONAL([ISLINUX],false)

AC_DEFINE([DARWIN],[1],[darwin])
AC_DEFINE([LINUX],[2],[linux])
AC_DEFINE([BSD],[3],[bsd])


case $host_os in
  darwin* )
        AM_CONDITIONAL([NEEDPTHREAD],false)
	AM_CONDITIONAL([ISDARWIN],true)
	AC_DEFINE([OSDETECTED],[DARWIN],[darwin])
	AC_DEFINE([CLOCK_REALTIME],[0],[for clock_gettime fake])	
	AC_DEFINE([CLOCK_MONOTONIC],[0],[for clock_gettime fake])
        ;;
  linux*)
        AM_CONDITIONAL([NEEDPTHREAD],true)
	AM_CONDITIONAL([ISLINUX],true)	
	AC_DEFINE([OSDETECTED],[LINUX],[linux])	
        ;;
   *BSD*)
        AM_CONDITIONAL([NEEDPTHREAD],true)
	AC_DEFINE([OSDETECTED],[BSD],[openbsd/freebsd])	
        ;;
   *bsd*)
        AM_CONDITIONAL([NEEDPTHREAD],true)
	AC_DEFINE([OSDETECTED],[BSD],[openbsd/freebsd])	
        ;;
    *)

        AC_MSG_ERROR([Your platform is not currently supported])
        ;;
esac

if test "x$CLANG" = xyes; then
AM_CONDITIONAL([CLANG],true)
else
AM_CONDITIONAL([CLANG],false)
fi

AC_ARG_ENABLE([writecrap],
    AS_HELP_STRING([--enable-writecrap], [Enable really verbose output]))

AS_IF([test "$enable_writecrap" = "yes"], [
	AC_DEFINE([WRITEC00CRAP],[],[write really verbose stdouts])
])




AC_ARG_ENABLE([c00guardian],
[  --disable-c00guardian    disable guardian],
[case "${enableval}" in
  yes) c00guardian=true ;;
  no)  c00guardian=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-c00guardian]) ;;
esac],[c00guardian=true])
AM_CONDITIONAL([C00WITHGUARDIAN], [test "x$c00guardian" = xtrue])
AS_IF([test "x$c00guardian" = xtrue],[AC_DEFINE([C00WITHGUARDIAN],[],[has guardian])])



AC_OUTPUT
