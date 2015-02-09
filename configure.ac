#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([c00clupea], [01], [christoph.pohl0@hm.edu])
#AC_CONFIG_SRCDIR([src/config.c])
#AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([subdir-objects])
# Checks for programs.

AC_PROG_CC(clang gcc)

# this is for automakes beyond 1.14
AM_PROG_CC_C_O

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h limits.h netinet/in.h stdlib.h string.h sys/socket.h syslog.h unistd.h stdarg.h limits.h stdio.h sys/types.h sys/utsname.h getopt.h pwd.h stdint.h fcntl.h sys/stat.h sys/mman.h errno.h syslog.h ctype.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset socket strstr pthread_mutex_lock snprintf va_start vsnprintf])

#AC_SEARCH_LIBS([zmq_ctx_new],[zmq],,[AC_MSG_ERROR(libzmq not installed)] )

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

AM_CONDITIONAL([ISDARWIN],false)

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

#standard log len
AC_ARG_VAR([C00_COPY_BUF_KB],[define the default copy buffer (default is 64)])

if test "x${C00_COPY_BUF_KB}" = "x"; then
	AC_DEFINE([C00_COPY_BUF_KB],[4],[default copy buffer kb])
else
	AC_DEFINE([C00_COPY_BUF_KB],[x${C00_COPY_BUF_KB}],[default copy buffer])
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

#main config
AC_ARG_VAR([MAINHMCONFIG],[main config (default is (sysconfdir)/c00clupea/c00clupea_hm.config)])

if test "x${MAINHMCONFIG}" = "x"; then
	AC_DEFINE([MAINHMCONFIG],["/etc/c00clupea/c00clupea_hm.config"],[inet family])
else
	AC_DEFINE([MAINHMCONFIG],[x${MAINHMCONFIG}],[inet family])
fi

AC_ARG_VAR([MAINHMCMDBUFFER],[hm main command buffer size, default 1024])

if test "x${MAINHMCMDBUFFER}" = "x"; then
	AC_DEFINE([MAINHMCMDBUFFER],[1024],[inet family])
else
	AC_DEFINE([MAINHMCMDBUFFER],[x${MAINHMCMDBUFFER}],[inet family])
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


AC_ARG_ENABLE([c00clupeabox],
[  --disable-c00clupeabox    disable box compile],
[case "${enableval}" in
  yes) c00clupeabox=true ;;
  no)  c00clupeabox=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-c00clupeabox]) ;;
esac],[c00clupeabox=true])
AM_CONDITIONAL([C00CLUPEABOX], [test "x$c00clupeabox" = xtrue])
#AM_CONDITIONAL([C00SUNAME], )
AS_IF([test "x$c00clupeabox" = xtrue],[AC_DEFINE([C00CLUPEABOX],[],[compile c00clupeabox])])

AC_ARG_ENABLE([c00measuretools],
[  --disable-c00measuretools    disable measurementtools],
[case "${enableval}" in
  yes) c00measuretools=true ;;
  no)  c00measuretools=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-c00measuretools]) ;;
esac],[c00measuretools=true])
AM_CONDITIONAL([C00MEASURETOOL], [test "x$c00measuretools" = xtrue])
#AM_CONDITIONAL([C00SUNAME], )
AS_IF([test "x$c00measuretools" = xtrue],[AC_DEFINE([C00MEASURETOOL],[],[compile measurement tools])])



AC_ARG_ENABLE([c00clupea],
[  --disable-c00clupea    disable honeypot compile],
[case "${enableval}" in
  yes) c00clupea=true ;;
  no)  c00clupea=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-c00clupea]) ;;
esac],[c00clupea=true])
AM_CONDITIONAL([C00CLUPEA], [test "x$c00clupea" = xtrue])
#AM_CONDITIONAL([C00SUNAME], )
AS_IF([test "x$c00clupea" = xtrue],[AC_DEFINE([C00CLUPEA],[],[compile c00clupea])])



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
[  --disable-c00suptime    disable uptime (simple version)],
[case "${enableval}" in
  yes) c00suptime=true ;;
  no)  c00suptime=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-c00suptime]) ;;
esac],[c00suptime=true])
AM_CONDITIONAL([C00SUPTIME], [test "x$c00suptime" = xtrue])
AS_IF([test "x$c00suptime" = xtrue],[AC_DEFINE([C00SUPTIME],[],[has uptime])])

AC_ARG_ENABLE([c00susleep],
[  --disable-c00susleep    disable upsleep (simple version)],
[case "${enableval}" in
  yes) c00susleep=true ;;
  no)  c00susleep=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-c00susleep]) ;;
esac],[c00susleep=true])
AM_CONDITIONAL([C00SUSLEEP], [test "x$c00susleep" = xtrue])
AS_IF([test "x$c00susleep" = xtrue],[AC_DEFINE([C00SUSLEEP],[],[has usleep])])


AC_ARG_ENABLE([c00scat],
[  --disable-c00scat    disable upsleep (simple version)],
[case "${enableval}" in
  yes) c00scat=true ;;
  no)  c00scat=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-c00scat]) ;;
esac],[c00scat=true])
AM_CONDITIONAL([C00SCAT], [test "x$c00scat" = xtrue])
AS_IF([test "x$c00scat" = xtrue],[AC_DEFINE([C00SCAT],[],[has cat])])

AC_ARG_ENABLE([c00strue],
[  --disable-c00strue    disable true (simple version)],
[case "${enableval}" in
  yes) c00strue=true ;;
  no)  c00strue=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-c00strue]) ;;
esac],[c00strue=true])
AM_CONDITIONAL([C00STRUE], [test "x$c00strue" = xtrue])
AS_IF([test "x$c00strue" = xtrue],[AC_DEFINE([C00STRUE],[],[has true])])


AC_ARG_ENABLE([c00sfalse],
[  --disable-c00sfalse    disable false (simple version)],
[case "${enableval}" in
  yes) c00sfalse=true ;;
  no)  c00sfalse=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-c00sfalse]) ;;
esac],[c00sfalse=true])
AM_CONDITIONAL([C00SFalSE], [test "x$c00sfalse" = xtrue])
AS_IF([test "x$c00sfalse" = xtrue],[AC_DEFINE([C00SFalSE],[],[has false])])

AC_ARG_ENABLE([c00syes],
[  --disable-c00syes    disable yes (simple version)],
[case "${enableval}" in
  yes) c00syes=true ;;
  no)  c00syes=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-c00syes]) ;;
esac],[c00syes=true])
AM_CONDITIONAL([C00SYES], [test "x$c00syes" = xtrue])
AS_IF([test "x$c00syes" = xtrue],[AC_DEFINE([C00SYES],[],[has yes])])

AC_ARG_ENABLE([c00sstrings],
[  --disable-c00sstrings    disable strings (simple version)],
[case "${enableval}" in
  yes) c00sstrings=true ;;
  no)  c00sstrings=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-c00sstrings]) ;;
esac],[c00sstrings=true])
AM_CONDITIONAL([C00SSTRINGS], [test "x$c00sstrings" = xtrue])
AS_IF([test "x$c00sstrings" = xtrue],[AC_DEFINE([C00SSTRINGS],[],[has strings])])

AC_ARG_ENABLE([c00spasswd],
[  --disable-c00spasswd    disable passwd (simple version)],
[case "${enableval}" in
  yes) c00spasswd=true ;;
  no)  c00spasswd=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-c00spasswd]) ;;
esac],[c00spasswd=true])
AM_CONDITIONAL([C00SPASSWD], [test "x$c00spasswd" = xtrue])
AS_IF([test "x$c00spasswd" = xtrue],[AC_DEFINE([C00SPASSWD],[],[has passwd])])


AC_ARG_ENABLE([c00stouch],
[  --disable-c00stouch    disable touch (simple version)],
[case "${enableval}" in
  yes) c00stouch=true ;;
  no)  c00stouch=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-c00stouch]) ;;
esac],[c00stouch=true])
AM_CONDITIONAL([C00STOUCH], [test "x$c00stouch" = xtrue])
AS_IF([test "x$c00stouch" = xtrue],[AC_DEFINE([C00STOUCH],[],[has touch])])

AC_ARG_ENABLE([c00spwd],
[  --disable-c00spwd    disable pwd (simple version)],
[case "${enableval}" in
  yes) c00spwd=true ;;
  no)  c00spwd=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-c00spwd]) ;;
esac],[c00spwd=true])
AM_CONDITIONAL([C00SPWD], [test "x$c00spwd" = xtrue])
AS_IF([test "x$c00spwd" = xtrue],[AC_DEFINE([C00SPWD],[],[has pwd])])


AC_ARG_ENABLE([c00snice],
[  --disable-c00snice    disable nice (simple version)],
[case "${enableval}" in
  yes) c00snice=true ;;
  no)  c00snice=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-c00snice]) ;;
esac],[c00snice=true])
AM_CONDITIONAL([C00SNICE], [test "x$c00snice" = xtrue])
AS_IF([test "x$c00snice" = xtrue],[AC_DEFINE([C00SNICE],[],[has nice])])

AC_ARG_ENABLE([c00sshell],
[  --disable-c00sshell    disable shell (ash - like)],
[case "${enableval}" in
  yes) c00sshell=true ;;
  no)  c00sshell=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-c00sshell]) ;;
esac],[c00sshell=true])
AM_CONDITIONAL([C00SSHELL], [test "x$c00sshell" = xtrue])
AS_IF([test "x$c00sshell" = xtrue],[AC_DEFINE([C00SSHELL],[],[has shell])])

AC_ARG_ENABLE([c00swithlink],
[  --enable-c00swithlink    enable linked c00clupeabox (simple version)],
[case "${enableval}" in
  yes) c00swithlink=true ;;
  no)  c00swithlink=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-c00swithlink]) ;;
esac],[c00swithlink=false])
AM_CONDITIONAL([C00SWITHLINK], [test "x$c00swithlink" = xtrue])
AS_IF([test "x$c00swithlink" = xtrue],[AC_DEFINE([C00SWITHLINK],[],[has linked box])])

AC_ARG_ENABLE([c00swithprefix],
[  --disable-c00swithprefix    disable prefix for coreutils],
[case "${enableval}" in
  yes) c00swithprefix=true ;;
  no)  c00swithprefix=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-c00swithprefix]) ;;
esac],[c00swithprefix=true])
AM_CONDITIONAL([C00SWITHPREFIX], [test "x$c00swithprefix" = xtrue])
AS_IF([test "x$c00swithprefix" = xtrue],[AC_DEFINE([C00SWITHPREFIX],[],[has prefix])])


AC_OUTPUT

