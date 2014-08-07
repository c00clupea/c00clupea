/* src/conf.h.  Generated from conf.h.in by configure.  */
/* src/conf.h.in.  Generated from configure.ac by autoheader.  */

/* allowed opts */
#define ALLOWED_OPTS "Vhp:b:c:s:"

/* strict atomic build */
/* #undef ATOMIC */

/* Define to 1 if you have the <arpa/inet.h> header file. */
#define HAVE_ARPA_INET_H 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define to 1 if your system has a GNU libc compatible `malloc' function, and
   to 0 otherwise. */
#define HAVE_MALLOC 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `memset' function. */
#define HAVE_MEMSET 1

/* Define to 1 if you have the <netinet/in.h> header file. */
#define HAVE_NETINET_IN_H 1

/* Define to 1 if you have the `pthread_mutex_lock' function. */
#define HAVE_PTHREAD_MUTEX_LOCK 1

/* Define to 1 if you have the `snprintf' function. */
#define HAVE_SNPRINTF 1

/* Define to 1 if you have the `socket' function. */
#define HAVE_SOCKET 1

/* Define to 1 if you have the <stdarg.h> header file. */
#define HAVE_STDARG_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdio.h> header file. */
#define HAVE_STDIO_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strstr' function. */
#define HAVE_STRSTR 1

/* Define to 1 if you have the <syslog.h> header file. */
#define HAVE_SYSLOG_H 1

/* Define to 1 if you have the <sys/socket.h> header file. */
#define HAVE_SYS_SOCKET_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the `va_start' function. */
/* #undef HAVE_VA_START */

/* Define to 1 if you have the `vsnprintf' function. */
#define HAVE_VSNPRINTF 1

/* inet family */
#define INET_FAM AF_INET

/* inet family */
#define LOG_MAIN_TEMPLATE "/var/log/c00clupea/c00clupea_%d.log"

/* inet family */
#define MAINCONFIG "/etc/c00clupea/c00clupea.config"

/* main buffer len */
#define MAIN_BUFFER_LEN 1024

/* Name of package */
#define PACKAGE "c00clupea"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "christoph.pohl0@hm.edu"

/* Define to the full name of this package. */
#define PACKAGE_NAME "c00clupea"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "c00clupea 01"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "c00clupea"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "01"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* standard error output */
#define STDERR stderr

/* syslog verific */
#define STDLOG LOG_NOTICE

/* default flush count */
#define STD_FLUSH_COUNT 1

/* default log LEN */
#define STD_LOG_LEN 1024

/* default log level */
#define STD_LOG_LVL 2

/* default strategy */
#define STRAT_DEFAULT 0

/* syslog verific */
#define SYSLOG LOG_DAEMON

/* tcp backlog len */
#define TCP_BACKLOG 128

/* build tests */
/* #undef USEC00TESTS */

/* Version number of package */
#define VERSION "01"

/* worker_pool size */
#define WORKER_POOL 10

/* write really verbose stdouts */
/* #undef WRITEC00CRAP */

/* Define to rpl_malloc if the replacement function should be used. */
/* #undef malloc */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */
