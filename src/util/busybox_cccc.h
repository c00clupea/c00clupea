#ifndef BUSY_BOX_CCCC_H
#define BUSY_BOX_CCCC_H
/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 */
/*#if ENABLE_LONG_OPTS || ENABLE_FEATURE_GETOPT_LONG*/
# include <getopt.h>
/*#endif*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <signal.h>



#include "../global.h"
#define type long long

#define FAST_FUNC

# define PUSH_AND_SET_FUNCTION_VISIBILITY_TO_HIDDEN /* nothing */
# define POP_SAVED_FUNCTION_VISIBILITY /* nothing */

#define ALIGN1 __attribute__((aligned(1)))
#define NOT_LONE_DASH(s) ((s)[0] != '-' || (s)[1])
#define isprint_asciionly(a) ((unsigned)((a) - 0x20) <= 0x7e - 0x20)
#define PRINT_NAME    2
#define PRINT_OFFSET  4
#define OFF_FMT "ll"


#define FAST_FUNC
#define UNUSED_PARAM __attribute__ ((__unused__))
/*#define UNUSED_PARAM*/

#define NORETURN __attribute__ ((__noreturn__))

#define ARRAY_SIZE(x) ((unsigned)(sizeof(x) / sizeof((x)[0])))

#if defined(i386) || defined(__x86_64__) || defined(__mips__) || defined(__cris__)
/* add other arches which benefit from this... */
typedef signed char smallint;
typedef unsigned char smalluint;
#else
/* for arches where byte accesses generate larger code: */
typedef int smallint;
typedef unsigned smalluint;
#endif

/* ISO C Standard:  7.16  Boolean type and values  <stdbool.h> */
#if (defined __digital__ && defined __unix__)
/* old system without (proper) C99 support */
# define bool smalluint
#else
/* modern system, so use it */
# include <stdbool.h>
#endif


#define bb_msg_read_error "read error"
#define bb_msg_write_error "write error"

typedef struct llist_t {
	struct llist_t *link;
	char *data;
} llist_t;

typedef unsigned long long uoff_t;

void llist_add_to(llist_t **old_head, void *data) FAST_FUNC;
void llist_add_to_end(llist_t **list_head, void *data) FAST_FUNC;
void *llist_pop(llist_t **elm) FAST_FUNC;
void llist_unlink(llist_t **head, llist_t *elm) FAST_FUNC;
void llist_free(llist_t *elm, void (*freeit)(void *data)) FAST_FUNC;
llist_t *llist_rev(llist_t *list) FAST_FUNC;
llist_t *llist_find_str(llist_t *first, const char *str) FAST_FUNC;
void * xzalloc(size_t size);

uint32_t FAST_FUNC getopt32(char **argv, const char *applet_opts, ...);
extern uint32_t option_mask32;


extern const char *const bb_argv_dash[];
extern const char bb_msg_standard_input[] ALIGN1;
extern const char bb_msg_standard_output[] ALIGN1;

FILE* fopen_or_warn_stdin(const char *filename);
FILE* fopen_or_warn(const char *path, const char *mode);

int open_or_warn_stdin(const char *filename);
int open_or_warn(const char *pathname, int flags);
int open3_or_warn(const char *pathname, int flags, int mode);

off_t bb_copyfd_eof(int fd1, int fd2);
off_t bb_full_fd_action(int src_fd, int dst_fd, off_t size);
ssize_t safe_read(int fd, void *buf, size_t count);
ssize_t full_write(int fd, const void *buf, size_t len);
ssize_t safe_write(int fd, const void *buf, size_t count);

void fflush_stdout_and_exit(int retval);
//void FAST_FUNC bb_perror_msg_and_die(const char *s, ...);
#endif
