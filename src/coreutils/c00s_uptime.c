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

int uptime_main(int UNUSED(argc), char UNUSED(*argv[])){
	struct tm *current_time;
	time_t current_secs;
	time(&current_secs);
	struct sysinfo info;
	sysinfo(&info);
	current_time = localtime(&current_secs);
	printf(" %02u:%02u:%02u",current_time->tm_hour, current_time->tm_min, current_time->tm_sec);
	return TRUE;
}
