/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	bb_signals.c
 * created: 	Wed Feb  4 16:11:53 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#include "util/busybox_cccc.h"


static const char signals[][7] = {
    // SUSv3 says kill must support these, and specifies the numerical values,
    // http://www.opengroup.org/onlinepubs/009695399/utilities/kill.html
    // {0, "EXIT"}, {1, "HUP"}, {2, "INT"}, {3, "QUIT"},
    // {6, "ABRT"}, {9, "KILL"}, {14, "ALRM"}, {15, "TERM"}
    // And Posix adds the following:
    // {SIGILL, "ILL"}, {SIGTRAP, "TRAP"}, {SIGFPE, "FPE"}, {SIGUSR1, "USR1"},
    // {SIGSEGV, "SEGV"}, {SIGUSR2, "USR2"}, {SIGPIPE, "PIPE"}, {SIGCHLD, "CHLD"},
    // {SIGCONT, "CONT"}, {SIGSTOP, "STOP"}, {SIGTSTP, "TSTP"}, {SIGTTIN, "TTIN"},
    // {SIGTTOU, "TTOU"}

    [0] = "EXIT",
#ifdef SIGHUP
    [SIGHUP   ] = "HUP",
#endif
#ifdef SIGINT
    [SIGINT   ] = "INT",
#endif
#ifdef SIGQUIT
    [SIGQUIT  ] = "QUIT",
#endif
#ifdef SIGILL
    [SIGILL   ] = "ILL",
#endif
#ifdef SIGTRAP
    [SIGTRAP  ] = "TRAP",
#endif
#ifdef SIGABRT
    [SIGABRT  ] = "ABRT",
#endif
#ifdef SIGBUS
    [SIGBUS   ] = "BUS",
#endif
#ifdef SIGFPE
    [SIGFPE   ] = "FPE",
#endif
#ifdef SIGKILL
    [SIGKILL  ] = "KILL",
#endif
#ifdef SIGUSR1
    [SIGUSR1  ] = "USR1",
#endif
#ifdef SIGSEGV
    [SIGSEGV  ] = "SEGV",
#endif
#ifdef SIGUSR2
    [SIGUSR2  ] = "USR2",
#endif
#ifdef SIGPIPE
    [SIGPIPE  ] = "PIPE",
#endif
#ifdef SIGALRM
    [SIGALRM  ] = "ALRM",
#endif
#ifdef SIGTERM
    [SIGTERM  ] = "TERM",
#endif
#ifdef SIGSTKFLT
    [SIGSTKFLT] = "STKFLT",
#endif
#ifdef SIGCHLD
    [SIGCHLD  ] = "CHLD",
#endif
#ifdef SIGCONT
    [SIGCONT  ] = "CONT",
#endif
#ifdef SIGSTOP
    [SIGSTOP  ] = "STOP",
#endif
#ifdef SIGTSTP
    [SIGTSTP  ] = "TSTP",
#endif
#ifdef SIGTTIN
    [SIGTTIN  ] = "TTIN",
#endif
#ifdef SIGTTOU
    [SIGTTOU  ] = "TTOU",
#endif
#ifdef SIGURG
    [SIGURG   ] = "URG",
#endif
#ifdef SIGXCPU
    [SIGXCPU  ] = "XCPU",
#endif
#ifdef SIGXFSZ
    [SIGXFSZ  ] = "XFSZ",
#endif
#ifdef SIGVTALRM
    [SIGVTALRM] = "VTALRM",
#endif
#ifdef SIGPROF
    [SIGPROF  ] = "PROF",
#endif
#ifdef SIGWINCH
    [SIGWINCH ] = "WINCH",
#endif
#ifdef SIGPOLL
    [SIGPOLL  ] = "POLL",
#endif
#ifdef SIGPWR
    [SIGPWR   ] = "PWR",
#endif
#ifdef SIGSYS
    [SIGSYS   ] = "SYS",
#endif
#if ENABLE_FEATURE_RTMINMAX
# ifdef __SIGRTMIN
    [__SIGRTMIN] = "RTMIN",
# endif
// This makes array about x2 bigger.
// More compact approach is to special-case SIGRTMAX in print_signames()
//# ifdef __SIGRTMAX
//	[__SIGRTMAX] = "RTMAX",
//# endif
#endif
};

int FAST_FUNC sigprocmask_allsigs(int how)
{
    sigset_t set;
    sigfillset(&set);
    return sigprocmask(how, &set, NULL);
}

/* Saves 2 bytes on x86! Oh my... */
int FAST_FUNC sigaction_set(int signum, const struct sigaction *act)
{
    return sigaction(signum, act, NULL);
}


const char *FAST_FUNC get_signame(int number)
{
    if ((unsigned)number < ARRAY_SIZE(signals)) {
        if (signals[number][0]) /* if it's not an empty str */
            return signals[number];
    }

    return itoa(number);
}

int FAST_FUNC get_signum(const char *name)
{
    unsigned i;
    i = bb_strtou(name, NULL, 10);

    if (!errno)
        return i;

    if (strncasecmp(name, "SIG", 3) == 0)
        name += 3;

    for (i = 0; i < ARRAY_SIZE(signals); i++)
        if (strcasecmp(name, signals[i]) == 0)
            return i;

#if ENABLE_DESKTOP
# if defined(SIGIOT) || defined(SIGIO)

    /* SIGIO[T] are aliased to other names,
     * thus cannot be stored in the signals[] array.
     * Need special code to recognize them */
    if ((name[0] | 0x20) == 'i' && (name[1] | 0x20) == 'o') {
#  ifdef SIGIO

        if (!name[2])
            return SIGIO;

#  endif
#  ifdef SIGIOT

        if ((name[2] | 0x20) == 't' && !name[3])
            return SIGIOT;

#  endif
    }

# endif
#endif
#if ENABLE_FEATURE_RTMINMAX
# if defined(SIGRTMIN) && defined(SIGRTMAX)
    /* libc may use some rt sigs for pthreads and therefore "remap" SIGRTMIN/MAX,
     * but we want to use "raw" SIGRTMIN/MAX. Underscored names, if exist, provide
     * them. If they don't exist, fall back to non-underscored ones: */
#  if !defined(__SIGRTMIN)
#   define __SIGRTMIN SIGRTMIN
#  endif
#  if !defined(__SIGRTMAX)
#   define __SIGRTMAX SIGRTMAX
#  endif

    if (strncasecmp(name, "RTMIN", 5) == 0) {
        if (!name[5])
            return __SIGRTMIN;

        if (name[5] == '+') {
            i = bb_strtou(name + 6, NULL, 10);

            if (!errno && i <= __SIGRTMAX - __SIGRTMIN)
                return __SIGRTMIN + i;
        }
    }
    else if (strncasecmp(name, "RTMAX", 5) == 0) {
        if (!name[5])
            return __SIGRTMAX;

        if (name[5] == '-') {
            i = bb_strtou(name + 6, NULL, 10);

            if (!errno && i <= __SIGRTMAX - __SIGRTMIN)
                return __SIGRTMAX - i;
        }
    }

# endif
#endif
    return -1;
}

void FAST_FUNC print_signames(void)
{
    unsigned signo;

    for (signo = 1; signo < ARRAY_SIZE(signals); signo++) {
        const char *name = signals[signo];

        if (name[0])
            printf("%2u) %s\n", signo, name);
    }

#if ENABLE_FEATURE_RTMINMAX
# ifdef __SIGRTMAX
    printf("%2u) %s\n", __SIGRTMAX, "RTMAX");
# endif
#endif
}

