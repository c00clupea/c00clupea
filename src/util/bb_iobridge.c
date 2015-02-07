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

#define is_name(c)      ((c) == '_' || isalpha((unsigned char)(c)))
#define is_in_name(c)   ((c) == '_' || isalnum((unsigned char)(c)))

void FAST_FUNC bb_error_msg(const char *s, ...)
{
    //make nothing
}

extern void bb_perror_msg(const char *s, ...)
{
    //nothing
}


void FAST_FUNC bb_perror_msg_and_die(const char *s, ...)
{
    /*va_list p;

    va_start(p, s);
    * Guard against "<error message>: Success" *
    (s, p, errno ? strerror(errno) : NULL);
    va_end(p);*/
    exit(1);
}

ssize_t safe_read(int fd, void *buf, size_t count)
{
    ssize_t n;

    do {
        n = read(fd, buf, count);
    }
    while (n < 0 && errno == EINTR);

    return n;
}

ssize_t safe_write(int fd, const void *buf, size_t count)
{
    ssize_t n;

    do {
        n = write(fd, buf, count);
    }
    while (n < 0 && errno == EINTR);

    return n;
}

ssize_t full_write(int fd, const void *buf, size_t len)
{
    ssize_t cc;
    ssize_t total;
    total = 0;

    while (len) {
        cc = safe_write(fd, buf, len);

        if (cc < 0) {
            if (total) {
                /* we already wrote some! */
                /* user can do another write to know the error code */
                return total;
            }

            return cc;  /* write() returns -1 on failure. */
        }

        total += cc;
        buf = ((const char *)buf) + cc;
        len -= cc;
    }

    return total;
}


off_t FAST_FUNC bb_copyfd_eof(int fd1, int fd2)
{
    return bb_full_fd_action(fd1, fd2, 0);
}


off_t bb_full_fd_action(int src_fd, int dst_fd, off_t size)
{
    int status = -1;
    off_t total = 0;
    bool continue_on_write_error = 0;
#if C00_COPY_BUF_KB <= 4
    char buffer[C00_COPY_BUF_KB * 1024];
    enum {buffer_size = sizeof(buffer)};
#else
    char *buffer;
    int buffer_size;
#endif

    if (size < 0) {
        size = -size;
        continue_on_write_error = 1;
    }

#if C00_COPY_BUF_KB > 4

    if (size > 0 && size <= 4 * 1024) {
        goto use_small_buf;
    }

    buffer = mmap(NULL, C00_COPY_BUF_KB * 1024, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    buffer_size = C00_COPY_BUF_KB * 1024;

    if (buffer == MAP_FAILED) {
use_small_buf:
        buffer = alloca(4 * 1024);
        buffer_size = 4 * 1024;
    }

#endif

    if (src_fd < 0) {
        goto out;
    }

    if (!size) {
        size = buffer_size;
        status = 1;
    }

//	printf("buffer_size %d",buffer_size);

    while (1) {
        ssize_t rd;
        rd = safe_read(src_fd, buffer, size > buffer_size ? buffer_size : size);

        //rd = 0;
        if (!rd) {
            status = 0;
            break;
        }

        if (rd < 0) {
            printf(bb_msg_read_error);
            break;
        }

        if (dst_fd >= 0) {
            ssize_t wr = full_write(dst_fd, buffer, rd);

            if(wr < rd) {
                if(!continue_on_write_error) {
                    printf(bb_msg_write_error);
                    break;
                }

                dst_fd = -1;
            }
        }

        total += rd;

        if(status < 0) {
            size -= rd;

            if(!size) {
                status = 0;
                break;
            }
        }
    }

out:
#if C00_COPY_BUF_KB > 4

    if (buffer_size != 4 * 1024) {
        munmap(buffer, buffer_size);
    }

#endif
    return status ? -1 : total;
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

int open_or_warn_stdin(const char *filename)
{
    int fd = STDIN_FILENO;

    if(filename != bb_msg_standard_input && NOT_LONE_DASH(filename)) {
        fd = open_or_warn(filename, O_RDONLY);
    }

    return fd;
}

FILE *fopen_or_warn_stdin(const char *filename)
{
    FILE *fp = stdin;

    if(filename != bb_msg_standard_input && NOT_LONE_DASH(filename)) {
        fp = fopen_or_warn(filename, "r");
    }

    return fp;
}

FILE *fopen_or_warn(const char *path, const char *mode)
{
    FILE *fp = fopen(path, mode);

    if (!fp) {
        //printf("error: %s",path);
    }

    return fp;
}


const char *FAST_FUNC
endofname(const char *name)
{
    if (!is_name(*name))
        return name;

    while (*++name) {
        if (!is_in_name(*name))
            break;
    }

    return name;
}


void FAST_FUNC bb_show_usage(void)
{
    fprintf(stdout, "No help available %s", "");
}

