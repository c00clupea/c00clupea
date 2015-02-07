/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	c00s_find_pid_by_name.c
 * created: 	Thu Feb  5 16:51:17 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#include "busybox_cccc.h"

static int comm_match(procps_status_t *p, const char *procName)
{
    int argv1idx;
    const char *argv1;

    if (strncmp(p->comm, procName, 15) != 0)
        return 0; /* comm does not match */

    /* In Linux, if comm is 15 chars, it is truncated.
     * (or maybe the name was exactly 15 chars, but there is
     * no way to know that) */
    if (p->comm[14] == '\0')
        return 1; /* comm is not truncated - matches */

    /* comm is truncated, but first 15 chars match.
     * This can be crazily_long_script_name.sh!
     * The telltale sign is basename(argv[1]) == procName */

    if (!p->argv0)
        return 0;

    argv1idx = strlen(p->argv0) + 1;

    if (argv1idx >= p->argv_len)
        return 0;

    argv1 = p->argv0 + argv1idx;

    if (strcmp(bb_basename(argv1), procName) != 0)
        return 0;

    return 1;
}

/* This finds the pid of the specified process.
 * Currently, it's implemented by rummaging through
 * the proc filesystem.
 *
 * Returns a list of all matching PIDs
 * It is the caller's duty to free the returned pidlist.
 *
 * Modified by Vladimir Oleynik for use with libbb/procps.c
 */
pid_t *FAST_FUNC find_pid_by_name(const char *procName)
{
    pid_t *pidList;
    int i = 0;
    procps_status_t *p = NULL;
    pidList = xzalloc(sizeof(*pidList));

    while ((p = procps_scan(p, PSSCAN_PID | PSSCAN_COMM | PSSCAN_ARGVN | PSSCAN_EXE))) {
        if (comm_match(p, procName)
            /* or we require argv0 to match (essential for matching reexeced /proc/self/exe)*/
            || (p->argv0 && strcmp(bb_basename(p->argv0), procName) == 0)
            /* or we require /proc/PID/exe link to match */
            || (p->exe && strcmp(bb_basename(p->exe), procName) == 0)
           ) {
            pidList = xrealloc_vector(pidList, 2, i);
            pidList[i++] = p->pid;
        }
    }

    pidList[i] = 0;
    return pidList;
}
