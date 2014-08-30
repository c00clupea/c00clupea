#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([c00clupea], [01], [christoph.pohl0@hm.edu])
#AC_CONFIG_SRCDIR([src/config.c])
#AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([subdir-objects])
# Checks for programs.

AC_PROG_CC(clang gcc)


# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h limits.h netinet/in.h stdlib.h string.h sys/socket.h syslog.h unistd.h stdarg.h limits.h stdio.h sys/types.h sys/utsname.h getopt.h pwd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset socket strstr pthread_mutex_lock snprintf va_start vsnprintf])

AC_CONFIG_HEADERS([src/conf.h])

AC_CONFIG_FILES([Makefile src/Makefile man/Makefile])

AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([], [[
#ifndef __clang__
       not clang
#endif
]])],
[CLANG=yes], [CLANG=no])

AC_MSG_RESULT([$CLANG])

AC_CANONICAL_HOST

case $host_os in
  darwin* )
        AM_CONDITIONAL([NEEDPTHREAD],false)
        ;;
  linux*)
        AM_CONDITIONAL([NEEDPTHREAD],false)
        ;;
   *BSD*)
        AM_CONDITIONAL([NEEDPTHREAD],true)
        ;;
   *bsd*)
        AM_CONDITIONAL([NEEDPTHREAD],true)
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


#build tests

AC_ARG_ENABLE([buildtest],
    AS_HELP_STRING([--enable-buildtest], [Enable tests]))

AS_IF([test "$enable_buildtest" = "yes"], [
	AC_DEFINE([USEC00TESTS],[],[build tests])
])

AC_ARG_ENABLE([writecrap],
    AS_HELP_STRING([--enable-writecrap], [Enable really verbose output]))

AS_IF([test "$enable_writecrap" = "yes"], [
	AC_DEFINE([WRITEC00CRAP],[],[write really verbose stdouts])
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

#main tcp backlog
AC_ARG_VAR([TCP_BACKLOG],[define the tcp backlog len (default is 128)])

if test "x${TCP_BACKLOG}" = "x"; then
	AC_DEFINE([TCP_BACKLOG],[128],[tcp backlog len])
else
	AC_DEFINE([TCP_BACKLOG],[x${TCP_BACKLOG}],[tcp backlog len])
fi

#main stderr
AC_ARG_VAR([STDERR],[define the standard error output (default is stderr)])

if test "x${STDERR}" = "x"; then
	AC_DEFINE([STDERR],[stderr],[standard error output])
else
	AC_DEFINE([STDERR],[x${STDERR}],[standard error output])
fi

#default strategy
AC_ARG_VAR([STRAT_DEFAULT],[define the default strategy (default is 0)])

if test "x${STRAT_DEFAULT}" = "x"; then
	AC_DEFINE([STRAT_DEFAULT],[0],[default strategy])
else
	AC_DEFINE([STRAT_DEFAULT],[x${STRAT_DEFAULT}],[default strategy])
fi

#standard log lvl
AC_ARG_VAR([STD_LOG_LVL],[define the default log level (default is 2)])

if test "x${STD_LOG_LVL}" = "x"; then
	AC_DEFINE([STD_LOG_LVL],[2],[default log level])
else
	AC_DEFINE([STD_LOG_LVL],[x${STD_LOG_LVL}],[default log level])
fi

#standard log len
AC_ARG_VAR([STD_LOG_LEN],[define the default log leN (default is 1024)])

if test "x${STD_LOG_LEN}" = "x"; then
	AC_DEFINE([STD_LOG_LEN],[1024],[default log LEN])
else
	AC_DEFINE([STD_LOG_LEN],[x${STD_LOG_LEN}],[default log LEN])
fi

#standard FLUSH COUNT
AC_ARG_VAR([STD_FLUSH_COUNT],[define the default flush count (default is 1) flushes log after n logs to file n<= 1 == immediate])

if test "x${STD_FLUSH_COUNT}" = "x"; then
	AC_DEFINE([STD_FLUSH_COUNT],[1],[default flush count])
else
	AC_DEFINE([STD_FLUSH_COUNT],[x${STD_FLUSH_COUNT}],[default flush count])
fi

#allowed opts
AC_ARG_VAR([ALLOWED_OPTS],[allowed opts for commandline (default is <<Vhp:b:c:s:>>)])

if test "x${ALLOWED_OPTS}" = "x"; then
	AC_DEFINE([ALLOWED_OPTS],["Vhp:b:c:s:"],[allowed opts])
else
	AC_DEFINE([ALLOWED_OPTS],[x${ALLOWED_OPTS}],[allowed opts])
fi

#allowed inets
AC_ARG_VAR([INET_FAM],[inet family for sockets (default is AF_INET)])

if test "x${INET_FAM}" = "x"; then
	AC_DEFINE([INET_FAM],[AF_INET],[inet family])
else
	AC_DEFINE([INET_FAM],[x${INET_FAM}],[inet family])
fi

#main config
AC_ARG_VAR([MAINCONFIG],[main config (default is (sysconfdir)/c00clupea/c00clupea.config)])

if test "x${MAINCONFIG}" = "x"; then
	AC_DEFINE([MAINCONFIG],["/etc/c00clupea/c00clupea.config"],[inet family])
else
	AC_DEFINE([MAINCONFIG],[x${MAINCONFIG}],[inet family])
fi

#log template
AC_ARG_VAR([LOG_MAIN_TEMPLATE],[log template (default is (localstatedir)/log/c00clupea/c00clupea_%d.log)])

if test "x${LOG_MAIN_TEMPLATE}" = "x"; then
	AC_DEFINE([LOG_MAIN_TEMPLATE],["/var/log/c00clupea/c00clupea_%d.log"],[inet family])
else
	AC_DEFINE([LOG_MAIN_TEMPLATE],[x${LOG_MAIN_TEMPLATE}],[inet family])
fi

#strat config
AC_ARG_VAR([STRAT_CONFIG_PATH],[standard path for strategy configs (default is /etc/c00clupea)])

if test "x${STRAT_CONFIG_PATH}" = "x"; then
	AC_DEFINE([STRAT_CONFIG_PATH],["/etc/c00clupea"],[inet family])
else
	AC_DEFINE([STRAT_CONFIG_PATH],[x${STRAT_CONFIG_PATH}],[config path for strategies])
fi



AC_ARG_ENABLE([c00suname],
[  --disable-c00suname    disable uname],
[case "${enableval}" in
  yes) c00suname=true ;;
  no)  c00suname=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-c00suname]) ;;
esac],[c00suname=true])
AM_CONDITIONAL([C00SUNAME], [test "x$c00suname" = xtrue])
#AM_CONDITIONAL([C00SUNAME], )
AS_IF([test "x$c00suname" = xtrue],[AC_DEFINE([C00SUNAME],[],[has uname])])

AC_ARG_ENABLE([c00swhoami],
[  --disable-c00swhoami    disable whoami (simple version)],
[case "${enableval}" in
  yes) c00swhoami=true ;;
  no)  c00swhoami=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-c00swhoami]) ;;
esac],[c00swhoami=true])
AM_CONDITIONAL([C00SWHOAMI], [test "x$c00swhoami" = xtrue])
AS_IF([test "x$c00swhoami" = xtrue],[AC_DEFINE([C00SWHOAMI],[],[has whoami])])

AC_ARG_ENABLE([c00suptime],
[  --disable-c00uptime    disable uptime (simple version)],
[case "${enableval}" in
  yes) c00suptime=true ;;
  no)  c00suptime=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-c00suptime]) ;;
esac],[c00swhoami=true])
AM_CONDITIONAL([C00SUPTIME], [test "x$c00suptime" = xtrue])
AS_IF([test "x$c00suptime" = xtrue],[AC_DEFINE([C00SUPTIME],[],[has uptime])])

AC_OUTPUT

