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



void fflush_stdout_and_exit(int retval){
	if ( fflush(stdout) ){
//		bb_perror_msg_and_die(bb_msg_standard_output);
	}
	exit(retval);

}


void* FAST_FUNC xmalloc(size_t size)
{
	void *ptr = malloc(size);
	if (ptr == NULL && size != 0)
	{
		//	bb_error_msg_and_die(bb_msg_memory_exhausted);
		fprintf(stderr,"Out of memory %s","");
		exit(1);
	}
	return ptr;
}

void* FAST_FUNC xrealloc(void *ptr, size_t size)
{
	ptr = realloc(ptr, size);
	if (ptr == NULL && size != 0)
	{
		fprintf(stderr,"Out of memory %s","");
		exit(1);
		//	bb_error_msg_and_die(bb_msg_memory_exhausted);
	}
	return ptr;
}

void* FAST_FUNC xrealloc_vector_helper(void *vector, unsigned sizeof_and_shift, int idx)
{
	int mask = 1 << (uint8_t)sizeof_and_shift;

	if (!(idx & (mask - 1))) {
		sizeof_and_shift >>= 8; /* sizeof(vector[0]) */
		vector = xrealloc(vector, sizeof_and_shift * (idx + mask + 1));
		memset((char*)vector + (sizeof_and_shift * idx), 0, sizeof_and_shift * (mask + 1));
	}
	return vector;
}

char* FAST_FUNC xmalloc_readlink(const char *path)
{
	enum { GROWBY = 80 }; /* how large we will grow strings by */

	char *buf = NULL;
	int bufsize = 0, readsize = 0;

	do {
		bufsize += GROWBY;
		buf = xrealloc(buf, bufsize);
		readsize = readlink(path, buf, bufsize);
		if (readsize == -1) {
			free(buf);
			return NULL;
		}
	} while (bufsize < readsize + 1);

	buf[readsize] = '\0';

	return buf;
}


char* FAST_FUNC strchrnul(const char *s, int c)
{
	while (*s != '\0' && *s != c)
		s++;
	return (char*)s;
}

int FAST_FUNC fflush_all(void)
{
	return fflush(NULL);
}


// Die if we can't copy a string to freshly allocated memory.
char* FAST_FUNC xstrdup(const char *s)
{
	char *t;

	if (s == NULL)
		return NULL;

	t = strdup(s);

	if (t == NULL)
	{
		//	bb_error_msg_and_die(bb_msg_memory_exhausted);
		fprintf(stdout,"Out of memory %s","");
		exit(1);
	}
	return t;
}

DIR* FAST_FUNC xopendir(const char *path)
{
	DIR *dp;

	dp = opendir(path);
	if (!dp)
	{
		fprintf(stderr,"can't open '%s'", path);
		exit(1);
//bb_perror_msg_and_die("can't open '%s'", path);
	}
	return dp;
}

static char local_buf[sizeof(int) * 3];

/* Convert unsigned integer to ascii using a static buffer (returned). */
char* FAST_FUNC utoa(unsigned n)
{
	*(utoa_to_buf(n, local_buf, sizeof(local_buf) - 1)) = '\0';

	return local_buf;
}

/* Convert signed integer to ascii using a static buffer (returned). */
char* FAST_FUNC itoa(int n)
{
	*(itoa_to_buf(n, local_buf, sizeof(local_buf) - 1)) = '\0';

	return local_buf;
}


/* Convert signed integer to ascii, like utoa_to_buf() */
char* FAST_FUNC itoa_to_buf(int n, char *buf, unsigned buflen)
{
	if (!buflen)
		return buf;
	if (n < 0) {
		n = -n;
		*buf++ = '-';
		buflen--;
	}
	return utoa_to_buf((unsigned)n, buf, buflen);
}


/* Convert unsigned integer to ascii, writing into supplied buffer.
 * A truncated result contains the first few digits of the result ala strncpy.
 * Returns a pointer past last generated digit, does _not_ store NUL.
 */
void BUG_sizeof(void);
char* FAST_FUNC utoa_to_buf(unsigned n, char *buf, unsigned buflen)
{
	unsigned i, out, res;

	if (buflen) {
		out = 0;
		if (sizeof(n) == 4)
		// 2^32-1 = 4294967295
			i = 1000000000;
#if UINT_MAX > 4294967295 /* prevents warning about "const too large" */
		else
		if (sizeof(n) == 8)
		// 2^64-1 = 18446744073709551615
			i = 10000000000000000000;
#endif
		else
			BUG_sizeof();
		for (; i; i /= 10) {
			res = n / i;
			n = n % i;
			if (res || out || i == 1) {
				if (--buflen == 0)
					break;
				out++;
				*buf++ = '0' + res;
			}
		}
	}
	return buf;
}

void FAST_FUNC close_on_exec_on(int fd)
{
	fcntl(fd, F_SETFD, FD_CLOEXEC);
}



const char* FAST_FUNC bb_basename(const char *name)
{
	const char *cp = strrchr(name, '/');
	if (cp)
		return cp + 1;
	return name;
}


char* FAST_FUNC safe_strncpy(char *dst, const char *src, size_t size)
{
	if (!size) return dst;
	dst[--size] = '\0';
	return strncpy(dst, src, size);
}

static void get_mono(struct timespec *ts)
{
	if (syscall(__NR_clock_gettime, CLOCK_MONOTONIC, ts))
	{
		fprintf(stderr,"clock_gettime(MONOTONIC) failed %s","");
		exit(1);
		//	bb_error_msg_and_die("clock_gettime(MONOTONIC) failed");
	}
}

unsigned long long FAST_FUNC monotonic_ms(void)
{
	struct timespec ts;
	get_mono(&ts);
	return ts.tv_sec * 1000ULL + ts.tv_nsec/1000000;
}

ssize_t FAST_FUNC nonblock_immune_read(int fd, void *buf, size_t count, int loop_on_EINTR)
{
	struct pollfd pfd[1];
	ssize_t n;

	while (1) {
		n = loop_on_EINTR ? safe_read(fd, buf, count) : read(fd, buf, count);
		if (n >= 0 || errno != EAGAIN)
			return n;
		/* fd is in O_NONBLOCK mode. Wait using poll and repeat */
		pfd[0].fd = fd;
		pfd[0].events = POLLIN;
		/* note: safe_poll pulls in printf */
		loop_on_EINTR ? safe_poll(pfd, 1, -1) : poll(pfd, 1, -1);
	}
}
int FAST_FUNC safe_poll(struct pollfd *ufds, nfds_t nfds, int timeout)
{
	while (1) {
		int n = poll(ufds, nfds, timeout);
		if (n >= 0)
			return n;
		/* Make sure we inch towards completion */
		if (timeout > 0)
			timeout--;
		/* E.g. strace causes poll to return this */
		if (errno == EINTR)
			continue;
		/* Kernel is very low on memory. Retry. */
		/* I doubt many callers would handle this correctly! */
		if (errno == ENOMEM)
			continue;
		bb_perror_msg("poll");
		return n;
	}
}


char* FAST_FUNC concat_path_file(const char *path, const char *filename)
{
	char *lc;

	if (!path)
		path = "";
	lc = last_char_is(path, '/');
	while (*filename == '/')
		filename++;
	return xasprintf("%s%s%s", path, (lc==NULL ? "/" : ""), filename);
}


char* FAST_FUNC last_char_is(const char *s, int c)
{
	if (s && *s) {
		size_t sz = strlen(s) - 1;
		s += sz;
		if ( (unsigned char)*s == c)
			return (char*)s;
	}
	return NULL;
}

char* FAST_FUNC xasprintf(const char *format, ...)
{
	va_list p;
	int r;
	char *string_ptr;

	va_start(p, format);
	r = vasprintf(&string_ptr, format, p);
	va_end(p);

	if (r < 0)
	{
		fprintf(stderr,"Out of memory %s","");
		exit(1);
	}//		bb_error_msg_and_die(bb_msg_memory_exhausted);
	return string_ptr;
}
