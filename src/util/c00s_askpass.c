/**
 *
 * Some sourcecode in this file is shamelessly copied from another open source software
 * See the original license and developers below this header
 * However other parts in this sourcefile are adopted for the c00clupea Honeypot
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 */
/* vi: set sw=4 ts=4: */
/*
 * Ask for a password
 * I use a static buffer in this function.  Plan accordingly.
 *
 * Copyright (C) 1999-2004 by Erik Andersen <andersen@codepoet.org>
 *
 * Licensed under GPLv2 or later, see file LICENSE in this source tree.
 */

#include "include/c00s_libcu.h"

/* do nothing signal handler */
static void askpass_timeout(int UNUSED_PARAM ignore)
{
}

char* FAST_FUNC c00_ask_stdin(const char *prompt)
{
	return c00_ask(STDIN_FILENO, 0, prompt);
}
char* FAST_FUNC c00_ask(const int fd, int timeout, const char *prompt)
{
	/* Was static char[BIGNUM] */
	enum { sizeof_passwd = 128 };
	static char *passwd;

	char *ret;
	int i;
	struct sigaction sa, oldsa;
	struct termios tio, oldtio;

	fputs(prompt, stdout);
	fflush_all();
	tcflush(fd, TCIFLUSH);

	tcgetattr(fd, &oldtio);
	tio = oldtio;
#if 0
	/* Switch off UPPERCASE->lowercase conversion (never used since 198x)
	 * and XON/XOFF (why we want to mess with this??)
	 */
# ifndef IUCLC
#  define IUCLC 0
# endif
	tio.c_iflag &= ~(IUCLC|IXON|IXOFF|IXANY);
#endif
	/* Switch off echo */
	tio.c_lflag &= ~(ECHO|ECHOE|ECHOK|ECHONL);
	tcsetattr(fd, TCSANOW, &tio);

	memset(&sa, 0, sizeof(sa));
	/* sa.sa_flags = 0; - no SA_RESTART! */
	/* SIGINT and SIGALRM will interrupt reads below */
	sa.sa_handler = askpass_timeout;
	sigaction(SIGINT, &sa, &oldsa);
	if (timeout) {
		sigaction_set(SIGALRM, &sa);
		alarm(timeout);
	}

	if (!passwd)
		passwd = xmalloc(sizeof_passwd);
	ret = passwd;
	i = 0;
	while (1) {
		int r = read(fd, &ret[i], 1);
		if ((i == 0 && r == 0) /* EOF (^D) with no password */
		 || r < 0
		) {
			/* read is interrupted by timeout or ^C */
			ret = NULL;
			break;
		}
		if (r == 0 /* EOF */
		 || ret[i] == '\r' || ret[i] == '\n' /* EOL */
		 || ++i == sizeof_passwd-1 /* line limit */
		) {
			ret[i] = '\0';
			break;
		}
	}

	if (timeout) {
		alarm(0);
	}
	sigaction_set(SIGINT, &oldsa);
	tcsetattr(fd, TCSANOW, &oldtio);
	putchar('\n');
	fflush_all();
	return ret;
}
