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
#include <wait.h>
#include <sys/syscall.h>


/*some config*/
#define IF_KILL(...)__VA_ARGS__
#define IF_FEATURE_SHOW_THREADS(...) __VA_ARGS__
#define IF_SELINUX(...)
#define IF_ECHO(...)__VA_ARGS__


#define ENABLE_KILLALL 1
#define ENABLE_KILLALL5 1
#define ENABLE_PGREP 0
#define ENABLE_PKILL 1
#define ENABLE_PIDOF 1
#define ENABLE_SELINUX 0
#define ENABLE_SESTATUS 0
#define ENABLE_FEATURE_TOP_SMP_PROCESS 0
#define ENABLE_FEATURE_PS_ADDITIONAL_COLUMNS 0
#define ENABLE_FEATURE_TOPMEM 0
#define ENABLE_FEATURE_SHOW_THREADS 1
#define CONFIG_FEATURE_EDITING 0
#define ENABLE_FEATURE_EDITING 0
#define ENABLE_ASH 1

#define PROCPS_BUFSIZE 1024


/*make them configurable through autoconf, but later...**/
#ifndef BANNER
#define BANNER "C00clupea Honeypot"
#endif


#define CONFIG_BUSYBOX_EXEC_PATH "/proc/self/exe"
#define BB_ADDITIONAL_PATH

/*end refactor target for autoconf*/


#ifndef COMM_LEN
# ifdef TASK_COMM_LEN
enum { COMM_LEN = TASK_COMM_LEN };
# else
/* synchronize with sizeof(task_struct.comm) in /usr/include/linux/sched.h */
enum { COMM_LEN = 16 };
# endif
#endif

#include <unistd.h>
#define fdprintf dprintf


/*Here we will overwrite the libc...*/

#define barrier() __asm__ __volatile__("":::"memory")

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
#define isspace(a) ({ unsigned char bb__isspace = (a) - 9; bb__isspace == (' ' - 9) || bb__isspace <= (13 - 9); })
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

/*#include "util/c00s_xatonum.h"*/

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


int c00_strtoi(const char *args, int *val);
int c00_strtoipos(const char *args, int *val);
int c00_strtol(const char *args, long *val);
int c00_strtolpos(const char *args, long *val);
int c00_strtoi_in_range(const char *args, int *val, long min, long max);
unsigned bb_strtou(const char *arg, char **endp, int base) FAST_FUNC;
long long bb_strtoll(const char *arg, char **endp, int base) FAST_FUNC;
int bb_strtoi(const char *arg, char **endp, int base);
unsigned long long bb_strtoull(const char *arg, char **endp, int base) FAST_FUNC;
unsigned long bb_strtoul(const char *arg, char **endp, int base);


typedef unsigned long long uoff_t;

void llist_add_to(llist_t **old_head, void *data) FAST_FUNC;
void llist_add_to_end(llist_t **list_head, void *data) FAST_FUNC;
void *llist_pop(llist_t **elm) FAST_FUNC;
void llist_unlink(llist_t **head, llist_t *elm) FAST_FUNC;
void llist_free(llist_t *elm, void (*freeit)(void *data)) FAST_FUNC;
llist_t *llist_rev(llist_t *list) FAST_FUNC;
llist_t *llist_find_str(llist_t *first, const char *str) FAST_FUNC;
void * xzalloc(size_t size);



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

enum {
	PSSCAN_PID      = 1 << 0,
	PSSCAN_PPID     = 1 << 1,
	PSSCAN_PGID     = 1 << 2,
	PSSCAN_SID      = 1 << 3,
	PSSCAN_UIDGID   = 1 << 4,
	PSSCAN_COMM     = 1 << 5,
	/* PSSCAN_CMD      = 1 << 6, - use read_cmdline instead */
	PSSCAN_ARGV0    = 1 << 7,
	PSSCAN_EXE      = 1 << 8,
	PSSCAN_STATE    = 1 << 9,
	PSSCAN_VSZ      = 1 << 10,
	PSSCAN_RSS      = 1 << 11,
	PSSCAN_STIME    = 1 << 12,
	PSSCAN_UTIME    = 1 << 13,
	PSSCAN_TTY      = 1 << 14,
	PSSCAN_SMAPS	= (1 << 15) * ENABLE_FEATURE_TOPMEM,
	/* NB: used by find_pid_by_name(). Any applet using it
	 * needs to be mentioned here. */
	PSSCAN_ARGVN    = (1 << 16) * (ENABLE_KILLALL
				|| ENABLE_PGREP || ENABLE_PKILL
				|| ENABLE_PIDOF
				|| ENABLE_SESTATUS
				),
	PSSCAN_CONTEXT  = (1 << 17) * ENABLE_SELINUX,
	PSSCAN_START_TIME = 1 << 18,
	PSSCAN_CPU      = (1 << 19) * ENABLE_FEATURE_TOP_SMP_PROCESS,
	PSSCAN_NICE     = (1 << 20) * ENABLE_FEATURE_PS_ADDITIONAL_COLUMNS,
	PSSCAN_RUIDGID  = (1 << 21) * ENABLE_FEATURE_PS_ADDITIONAL_COLUMNS,
	PSSCAN_TASKS	= (1 << 22) * ENABLE_FEATURE_SHOW_THREADS,
};
/*functions*/

procps_status_t* procps_scan(procps_status_t* sp, int flags) FAST_FUNC;

void free_procps_scan(procps_status_t* sp) FAST_FUNC;
void close_on_exec_on(int fd) FAST_FUNC;

pid_t *find_pid_by_name(const char* procName) FAST_FUNC;

int kill_main(int argc, char **argv) EXTERNALLY_VISIBLE;
int echo_main(int argc, char** argv) IF_ECHO(MAIN_EXTERNALLY_VISIBLE);

uint32_t FAST_FUNC getopt32(char **argv, const char *applet_opts, ...);

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

int bb_parse_mode(const char* s, mode_t* theMode) FAST_FUNC;



void fflush_stdout_and_exit(int retval);
//void FAST_FUNC bb_perror_msg_and_die(const char *s, ...);
extern char *strchrnul(const char *s, int c) FAST_FUNC;

char *last_char_is(const char *s, int c) FAST_FUNC;

#define isxdigit(a) bb_ascii_isxdigit(a)
static inline int bb_ascii_isxdigit(unsigned char a)
{
	unsigned char b = a - '0';
	if (b <= 9)
		return (b <= 9);
	b = (a|0x20) - 'a';
	return b <= 'f' - 'a';
}


void FAST_FUNC bb_error_msg(const char *s, ...);

extern void bb_perror_msg(const char *s, ...) __attribute__ ((format (printf, 1, 2))) FAST_FUNC;
extern void bb_perror_msg_and_die(const char *s, ...) __attribute__ ((noreturn, format (printf, 1, 2))) FAST_FUNC;

extern void bb_show_usage(void) NORETURN FAST_FUNC;

const char *bb_basename(const char *name) FAST_FUNC;

extern char bb_process_escape_sequence(const char **ptr) FAST_FUNC;

int fflush_all(void) FAST_FUNC;

void *xmalloc(size_t size) FAST_FUNC RETURNS_MALLOC;
void *xrealloc(void *old, size_t size) FAST_FUNC;
#define xrealloc_vector(vector, shift, idx) \
	xrealloc_vector_helper((vector), (sizeof((vector)[0]) << 8) + (shift), (idx))
void* xrealloc_vector_helper(void *vector, unsigned sizeof_and_shift, int idx) FAST_FUNC;
char *xmalloc_readlink(const char *path) FAST_FUNC RETURNS_MALLOC;

int sigprocmask_allsigs(int how) FAST_FUNC;

const char *get_signame(int number) FAST_FUNC;

int get_signum(const char *name) FAST_FUNC;

int sigaction_set(int sig, const struct sigaction *act) FAST_FUNC;

void print_signames(void) FAST_FUNC;

char *xstrdup(const char *s) FAST_FUNC RETURNS_MALLOC;

char *safe_strncpy(char *dst, const char *src, size_t size) FAST_FUNC;

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

char *utoa(unsigned n) FAST_FUNC;
char *utoa_to_buf(unsigned n, char *buf, unsigned buflen) FAST_FUNC;

unsigned long long monotonic_ms(void) FAST_FUNC;

DIR *xopendir(const char *path) FAST_FUNC;

char *concat_path_file(const char *path, const char *filename) FAST_FUNC;

extern ssize_t nonblock_immune_read(int fd, void *buf, size_t count, int loop_on_EINTR) FAST_FUNC;

int safe_poll(struct pollfd *ufds, nfds_t nfds, int timeout_ms) FAST_FUNC;


char *xasprintf(const char *format, ...) __attribute__ ((format(printf, 1, 2))) FAST_FUNC RETURNS_MALLOC;

line_input_t *new_line_input_t(int flags) FAST_FUNC;

/*int read_line_input(line_input_t *st, const char *prompt, char *command, int maxsize, int timeout) FAST_FUNC;*/
int read_line_input(const char* prompt, char* command, int maxsize) FAST_FUNC;
#define read_line_input(state, prompt, command, maxsize, timeout) \
	read_line_input(prompt, command, maxsize)

#endif
