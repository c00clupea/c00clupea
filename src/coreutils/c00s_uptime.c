/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	c00s_uptime.c
 * created: 	Sat Aug 30 18:38:04 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#include "c00s_uptime.h"

int UPTIME_MAIN(int UNUSED(argc), char UNUSED(*argv[]))
{
    struct tm *current_time;
    time_t current_secs;
    time(&current_secs);
    struct c00b_sysinfo info;
    unsigned updays, uphours, upminutes;
    c00b_sysinfo(&info);
    current_time = localtime(&current_secs);
    upminutes = (unsigned) info.uptime / (unsigned)60;
    uphours = (upminutes / (unsigned)60) % (unsigned)24;
    upminutes %= 60;
    updays = (unsigned) info.uptime / (unsigned)(24 * 60 * 60);
    printf(" %02u:%02u:%02u up ", current_time->tm_hour, current_time->tm_min, current_time->tm_sec);

    if (updays) {
        printf("%u day%s, ", updays, (updays != 1) ? "s" : "");
    }

    if (uphours) {
        printf("%2u:%02u", uphours, upminutes);
    }
    else {
        printf("%u min", upminutes);
    }

    printf(",  load average: %u.%02u, %u.%02u, %u.%02u\n",
           LOAD_INT(info.loads[0]), LOAD_FRAC(info.loads[0]),
           LOAD_INT(info.loads[1]), LOAD_FRAC(info.loads[1]),
           LOAD_INT(info.loads[2]), LOAD_FRAC(info.loads[2]));
    return TRUE;
}
