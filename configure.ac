#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([c00clupea], [01], [christoph.pohl0@hm.edu])
#AC_CONFIG_SRCDIR([src/config.c])
#AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([subdir-objects])
# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h limits.h netinet/in.h stdlib.h string.h sys/socket.h syslog.h unistd.h stdarg.h limits.h stdio.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset socket strstr pthread_mutex_lock snprintf va_start vsnprintf])

AC_CONFIG_HEADERS([src/conf.h])

AC_CONFIG_FILES([Makefile src/Makefile man/Makefile])

#build tests

AC_ARG_ENABLE([buildtest],
    AS_HELP_STRING([--enable-buildtest], [Enable tests]))

AS_IF([test "$enable_buildtest" = "yes"], [
	AC_DEFINE([USEC00TESTS],[],[build tests])
])

#strict atomic 
AC_ARG_ENABLE([strict-atomic],
    AS_HELP_STRING([--enable-strict-atomic], [Enable strict atomic behaviour...It is safe but slow....]))

AS_IF([test "$enable_strict-atomic" = "yes"], [
	AC_DEFINE([ATOMIC],[],[strict atomic build])
])

#syslog daemon
AC_ARG_VAR([SYSLOG],[define the syslog daemon (default is LOG_DAEMON)])

if test "x${SYSLOG}" = "x"; then
	AC_DEFINE([SYSLOG],[LOG_DAEMON],[syslog verific])
else
	AC_DEFINE([SYSLOG],[x${SYSLOG}],[syslog verific])
fi

#syslog standardlog
AC_ARG_VAR([STDLOG],[define the syslog standardlog (default is LOG_NOTICE)])

if test "x${STDLOG}" = "x"; then
	AC_DEFINE([STDLOG],[LOG_NOTICE],[syslog standardlog])
else
	AC_DEFINE([STDLOG],[x${STDLOG}],[syslog verific])
fi

#worker pool
AC_ARG_VAR([WORKER_POOL],[define the worker pool size (default is 10)])

if test "x${WORKER_POOL}" = "x"; then
	AC_DEFINE([WORKER_POOL],[10],[worker pool size])
else
	AC_DEFINE([WORKER_POOL],[x${WORKER_POOL}],[worker_pool size])
fi

#main buffer len
AC_ARG_VAR([MAIN_BUFFER_LEN],[define the main buffer len (default is 1024)])

if test "x${MAIN_BUFFER_LEN}" = "x"; then
	AC_DEFINE([MAIN_BUFFER_LEN],[1024],[main buffer len])
else
	AC_DEFINE([MAIN_BUFFER_LEN],[x${MAIN_BUFFER_LEN}],[main buffer len])
fi
AC_OUTPUT

