/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 * 
 * File:	bb_flush.c
 * created: 	Mon Dec  1 08:01:38 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#include "busybox_cccc.h"
const char bb_msg_standard_input[] ALIGN1 = "standard input";
const char bb_msg_standard_output[] ALIGN1 = "standard output";


void fflush_stdout_and_exit(int retval){
	if ( fflush(stdout) ){
//		bb_perror_msg_and_die(bb_msg_standard_output);
	}
	exit(retval);

}


