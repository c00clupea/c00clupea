#ifndef C00B_SYSINFO
#define C00B_SYSINFO
/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	c00b_sysinfo.h
 * created: 	Sat Nov 24 18:37:56 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */

struct c00b_sysinfo{
	/*Borrowed from uclibc*/
	long uptime;			/* Seconds since boot */
	unsigned long loads[3];		/* 1, 5, and 15 minute load averages */
	unsigned long totalram;		/* Total usable main memory size */
	unsigned long freeram;		/* Available memory size */
	unsigned long sharedram;	/* Amount of shared memory */
	unsigned long bufferram;	/* Memory used by buffers */
	unsigned long totalswap;	/* Total swap space size */
	unsigned long freeswap;		/* swap space still available */
	unsigned short procs;		/* Number of current processes */
	unsigned short pad;			/* Padding needed for m68k */
	unsigned long totalhigh;	/* Total high memory size */
	unsigned long freehigh;		/* Available high memory size */
	unsigned int mem_unit;		/* Memory unit size in bytes */
};

int c00b_sysinfo (struct c00b_sysinfo *__info);

#endif /*C00B_SYSINFO*/
