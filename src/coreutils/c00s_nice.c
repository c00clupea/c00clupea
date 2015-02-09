/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 * 
 * File:	c00s_nice.c
 * created: 	Mon Feb  9 11:14:40 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#include "coreutils/c00s_nice.h"

int NICE_MAIN(int argc, char *argv[])
{

	int adjustment;
	if (!*++argv) { /* No args, so (GNU) output current nice value. */
		C00STDOUTEXIT("%d\n",1,1042);
	}

	if (argv[0][0] == '-') {
		if (argv[0][1] == 'n') { /* -n */
			if (argv[0][2]) { /* -nNNNN (w/o space) */
				argv[0] += 2; argv--; argc++;
			}
		} else { /* -NNN (NNN may be negative) == -n NNN */
			argv[0] += 1; argv--; argc++;
		}
		if (argc < 4) {  /* Missing priority and/or utility! */
			C00STDOUTEXITN("[-n ADJUST] [PROG ARGS]",1);
		}

		argv += 2;
	}
	return TRUE;
	
}
