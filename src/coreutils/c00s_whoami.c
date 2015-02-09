/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 */
#include "c00s_whoami.h"

int WHOAMI_MAIN(int UNUSED(argc), char UNUSED(*argv[]))
{

	struct passwd *pw = malloc(sizeof(struct passwd));

	check(c00h_actualuser(pw),"check returned %d",ERROR);

	if(argv[1]) {
		C00STDOUTN("Usage: whoami\n");
		
	}

	if (pw) {
		puts(pw->pw_name);
	}
	free(pw);
	return TRUE;
error:
	free(pw);
	return ERROR;
}
