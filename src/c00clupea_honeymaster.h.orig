/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 * 
 * File:	c00clupea_honeymaster.h
 * created: 	Mon Dec  1 17:31:09 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#ifndef C00CLUPEA_HONEYMASTER_H
#define C00CLUPEA_HONEYMASTER_H
#include "global.h"
#include <signal.h>
#include <sys/time.h>
#include "util/ringbuffer.h"

#include "util/c00_iniparser.h"

#include "util/util.h"
/**
 * init buffer for cmd (ringbuffer)
 * init threadpool
 * iter thread creation
 * -->work until signal
 * end by sig
 * free evth
 * destroy ringbuffer
 **/

#define NANO_SECOND_MULTIPLIER  1000000
#define C00_CMD_TIME_TICK 0x001

struct c00hm_config{
	int workerthreads;
int loglvl;
};

struct c00hm_command{
	unsigned short command;
};

int main( int argc, const char* argv[] );


#endif /* C00CLUPEA_HONEYMASTER_H */
