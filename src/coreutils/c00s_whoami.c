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
    uid_t uid = geteuid();
    struct passwd *pw = getpwuid(uid);

    if(argv[1]) {
        printf("Usage: whoami");
    }

    if (pw) {
        puts(pw->pw_name);
        return TRUE;
    }

    exit(1);
}
