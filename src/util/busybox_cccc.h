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
#if ENABLE_LONG_OPTS || ENABLE_FEATURE_GETOPT_LONG
# include <getopt.h>
#endif
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
#include <stddef.h>
#include <termios.h>
#include <poll.h>
#include <dirent.h>
#include <pwd.h>


/*some config*/
#define IF_KILL(...)__VA_ARGS__
#define IF_FEATURE_SHOW_THREADS(...) __VA_ARGS__
#define IF_SELINUX(...)

#ifndef COMM_LEN
# ifdef TASK_COMM_LEN
enum { COMM_LEN = TASK_COMM_LEN };
# else
/* synchronize with sizeof(task_struct.comm) in /usr/include/linux/sched.h */
enum { COMM_LEN = 16 };
# endif
#endif



/*Here we will overwrite the libc...*/



/*#include "../global.h"*/
#include "util.h"
#define type long long

#define FAST_FUNC

# define PUSH_AND_SET_FUNCTION_VISIBILITY_TO_HIDDEN /* nothing */
# define POP_SAVED_FUNCTION_VISIBILITY /* nothing */

#define ALIGN1 __attribute__((aligned(1)))
#define ALIGN2 __attribute__((aligned(2)))

#define RETURNS_MALLOC __attribute__ ((malloc))

#define EXTERNALLY_VISIBLE
#define MAIN_EXTERNALLY_VISIBLE EXTERNALLY_VISIBLE

#define NOT_LONE_DASH(s) ((s)[0] != '-' || (s)[1])
#define isprint_asciionly(a) ((unsigned)((a) - 0x20) <= 0x7e - 0x20)
#define PRINT_NAME    2
#define PRINT_OFFSET  4
#define OFF_FMT "ll"


#undef isalpha
#undef isdigit
#define isalpha(a) ((unsigned char)(((a)|0x20) - 'a') <= ('z' - 'a'))
#define isalnum(a) bb_ascii_isalnum(a)
#define isdigit(a) ((unsigned char)((a) - '0') <= 9)
static inline int bb_ascii_isalnum(unsigned char a)
{
	unsigned char b = a - '0';
	if (b <= 9)
		return (b <= 9);
	b = (a|0x20) - 'a';
	return b <= 'z' - 'a';
}

#define bb_dev_null "/dev/null"

/**#####################
 * This is a bloody Hack
 **#####################
 *  here we overwrite sth
 * <*))><
 */
/*
enum {
	DO_HISTORY       = 1 * (MAX_HISTORY > 0),
	TAB_COMPLETION   = 2 * ENABLE_FEATURE_TAB_COMPLETION,
	USERNAME_COMPLETION = 4 * ENABLE_FEATURE_USERNAME_COMPLETION,
	VI_MODE          = 8 * ENABLE_FEATURE_EDITING_VI,
	WITH_PATH_LOOKUP = 0x10,
	FOR_SHELL        = DO_HISTORY | TAB_COMPLETION | USERNAME_COMPLETION,
};
*/

enum {
	DO_HISTORY       = 0,
	TAB_COMPLETION   = 2 * 1,
	USERNAME_COMPLETION = 4 * 0,
	VI_MODE          = 8 * 0,
	WITH_PATH_LOOKUP = 0x10,
	FOR_SHELL        = 0 | 2 | 0,
};

#define FAST_FUNC
#define UNUSED_PARAM __attribute__ ((__unused__))
/*#define UNUSED_PARAM*/

#define NORETURN __attribute__ ((__noreturn__))

#define ARRAY_SIZE(x) ((unsigned)(sizeof(x) / sizeof((x)[0])))

#define LONE_DASH(s)     ((s)[0] == '-' && !(s)[1])

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

#include "util/c00s_xatonum.h"

extern const char bb_msg_requires_arg[] ALIGN1;


typedef struct line_input_t {
	int flags;
	const char *path_lookup;
# if MAX_HISTORY
	int cnt_history;
	int cur_history;
	int max_history; /* must never be <= 0 */
#  if ENABLE_FEATURE_EDITING_SAVEHISTORY
	/* meaning of this field depends on FEATURE_EDITING_SAVE_ON_EXIT:
	 * if !FEATURE_EDITING_SAVE_ON_EXIT: "how many lines are
	 * in on-disk history"
	 * if FEATURE_EDITING_SAVE_ON_EXIT: "how many in-memory lines are
	 * also in on-disk history (and thus need to be skipped on save)"
	 */
	unsigned cnt_history_in_file;
	const char *hist_file;
#  endif
	char *history[MAX_HISTORY + 1];
# endif
} line_input_t;

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


void close_on_exec_on(int fd) FAST_FUNC;

int kill_main(int argc, char **argv) EXTERNALLY_VISIBLE;

uint32_t FAST_FUNC getopt32(char **argv, const char *applet_opts, ...);

# define NOINLINE      __attribute__((__noinline__))

extern uint32_t option_mask32;




extern const char *const bb_argv_dash[];
extern const char bb_msg_standard_input[] ALIGN1;
extern const char bb_msg_standard_output[] ALIGN1;

extern const char bb_PATH_root_path[] ALIGN1; /* "PATH=/sbin:/usr/sbin:/bin:/usr/bin" */
#define bb_default_path      (bb_PATH_root_path + sizeof("PATH=/sbin:/usr/sbin"))

extern const char bb_msg_memory_exhausted[] ALIGN1;

extern const char bb_busybox_exec_path[] ALIGN1;
extern const char bb_banner[] ALIGN1;

/*structs*/

typedef struct procps_status_t {
	DIR *dir;
	IF_FEATURE_SHOW_THREADS(DIR *task_dir;)
	uint8_t shift_pages_to_bytes;
	uint8_t shift_pages_to_kb;
/* Fields are set to 0/NULL if failed to determine (or not requested) */
	uint16_t argv_len;
	char *argv0;
	char *exe;
	IF_SELINUX(char *context;)
	IF_FEATURE_SHOW_THREADS(unsigned main_thread_pid;)
	/* Everything below must contain no ptrs to malloc'ed data:
	 * it is memset(0) for each process in procps_scan() */
	unsigned long vsz, rss; /* we round it to kbytes */
	unsigned long stime, utime;
	unsigned long start_time;
	unsigned pid;
	unsigned ppid;
	unsigned pgid;
	unsigned sid;
	unsigned uid;
	unsigned gid;
#if ENABLE_FEATURE_PS_ADDITIONAL_COLUMNS
	unsigned ruid;
	unsigned rgid;
	int niceness;
#endif
	unsigned tty_major,tty_minor;
#if ENABLE_FEATURE_TOPMEM
	struct smaprec smaps;
#endif
	char state[4];
	/* basename of executable in exec(2), read from /proc/N/stat
	 * (if executable is symlink or script, it is NOT replaced
	 * by link target or interpreter name) */
	char comm[COMM_LEN];
	/* user/group? - use passwd/group parsing functions */
#if ENABLE_FEATURE_TOP_SMP_PROCESS
	int last_seen_on_cpu;
#endif
} procps_status_t;


/*functions*/


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
extern char *strchrnul(const char *s, int c) FAST_FUNC;


void FAST_FUNC bb_error_msg(const char *s, ...);

extern void bb_show_usage(void) NORETURN FAST_FUNC;

int fflush_all(void) FAST_FUNC;

void *xmalloc(size_t size) FAST_FUNC RETURNS_MALLOC;
void *xrealloc(void *old, size_t size) FAST_FUNC;

int sigprocmask_allsigs(int how) FAST_FUNC;

const char *get_signame(int number) FAST_FUNC;

int get_signum(const char *name) FAST_FUNC;

int sigaction_set(int sig, const struct sigaction *act) FAST_FUNC;

void print_signames(void) FAST_FUNC;

char *xstrdup(const char *s) FAST_FUNC RETURNS_MALLOC;

#if defined __GLIBC__ \
 || defined __UCLIBC__ \
 || defined __dietlibc__ \
 || defined __BIONIC__ \
 || defined _NEWLIB_VERSION
# include <features.h>
#endif

extern char **environ;

const char* endofname(const char *name) FAST_FUNC;

char *itoa(int n) FAST_FUNC;
char *itoa_to_buf(int n, char *buf, unsigned buflen) FAST_FUNC;

char *utoa_to_buf(unsigned n, char *buf, unsigned buflen) FAST_FUNC;


procps_status_t* procps_scan(procps_status_t* sp, int flags) FAST_FUNC;
#endif
