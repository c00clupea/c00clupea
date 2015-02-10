/* src/conf.h.  Generated from conf.h.in by configure.  */
/* src/conf.h.in.  Generated from configure.ac by autoheader.  */

/* bsd */
#define BSD 3

/* has guardian */
#define C00WITHGUARDIAN /**/

/* for clock_gettime fake */
#define CLOCK_MONOTONIC 0

/* for clock_gettime fake */
#define CLOCK_REALTIME 0

/* darwin */
#define DARWIN 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if your system has a GNU libc compatible `malloc' function, and
   to 0 otherwise. */
#define HAVE_MALLOC 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* linux */
#define LINUX 2

/* openbsd/freebsd */
#define OSDETECTED DARWIN

/* Name of package */
#define PACKAGE "c00clupeakernel"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "christoph.pohl0@hm.edu"

/* Define to the full name of this package. */
#define PACKAGE_NAME "c00clupeakernel"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "c00clupeakernel 01"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "c00clupeakernel"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "01"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Version number of package */
#define VERSION "01"

/* write really verbose stdouts */
/* #undef WRITEC00CRAP */

/* Define to 1 if `lex' declares `yytext' as a `char *' by default, not a
   `char[]'. */
#define YYTEXT_POINTER 1

/* Define to rpl_malloc if the replacement function should be used. */
/* #undef malloc */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */
