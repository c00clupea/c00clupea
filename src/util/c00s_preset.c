/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	c00s_preset.c
 * created: 	Sat Feb  7 11:13:26 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#include "busybox_cccc.h"

const char bb_banner[] ALIGN1 = BANNER;
const char bb_busybox_exec_path[] ALIGN1 = CONFIG_BUSYBOX_EXEC_PATH;
const char bb_PATH_root_path[] ALIGN1 =
    "PATH=/sbin:/usr/sbin:/bin:/usr/bin" BB_ADDITIONAL_PATH;


const char bb_msg_memory_exhausted[] ALIGN1 = "out of memory";
const char bb_msg_invalid_date[] ALIGN1 = "invalid date '%s'";
const char bb_msg_unknown[] ALIGN1 = "(unknown)";
const char bb_msg_can_not_create_raw_socket[] ALIGN1 = "can't create raw socket";
const char bb_msg_perm_denied_are_you_root[] ALIGN1 = "permission denied (are you root?)";
const char bb_msg_you_must_be_root[] ALIGN1 = "you must be root";
const char bb_msg_requires_arg[] ALIGN1 = "%s requires an argument";
const char bb_msg_invalid_arg[] ALIGN1 = "invalid argument '%s' to '%s'";
const char bb_msg_standard_input[] ALIGN1 = "standard input";
const char bb_msg_standard_output[] ALIGN1 = "standard output";
