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

static char local_buf[sizeof(int) * 3];

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

