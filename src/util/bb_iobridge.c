/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 * 
 * File:	bb_iobridge.c
 * created: 	Thu Nov 27 13:53:21 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#include "busybox_cccc.h"

const char bb_msg_standard_input[] ALIGN1 = "standard input";

off_t FAST_FUNC bb_copyfd_eof(int fd1, int fd2)
{
	return bb_full_fd_action(fd1, fd2, 0);
}


off_t bb_full_fd_action(int src_fd, int dst_fd, off_t size){
	int status = -1;
	off_t total = 0;
	bool continue_on_write_error = 0;
	char *buffer;
	int buffer_size;
	if (size < 0){
		size = -size;
		continue_on_write_error = 1;
	}

}

int open3_or_warn(const char *pathname, int flags, int mode)
{
	int ret;

	ret = open(pathname, flags, mode);
	if (ret < 0) {
		printf("can't open '%s'", pathname);
	}
	return ret;
}

// Warn if we can't open a file and return a fd.
int open_or_warn(const char *pathname, int flags)
{
	return open3_or_warn(pathname, flags, 0666);
}

int open_or_warn_stdin(const char *filename){
	int fd = STDIN_FILENO;
	if(filename != bb_msg_standard_input && NOT_LONE_DASH(filename)){
		open_or_warn(filename, O_RDONLY);
	}
	return fd;

	
}
