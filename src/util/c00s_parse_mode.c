/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	c00s_parse_mode.c
 * created: 	Fri Feb  6 09:13:20 2015
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */

#include "include/c00s_libcu.h"

#define FILEMODEBITS (S_ISUID | S_ISGID | S_ISVTX | S_IRWXU | S_IRWXG | S_IRWXO)

int FAST_FUNC bb_parse_mode(const char *s, mode_t *current_mode)
{
    static const mode_t who_mask[] = {
        S_ISUID | S_ISGID | S_ISVTX | S_IRWXU | S_IRWXG | S_IRWXO, /* a */
        S_ISUID | S_IRWXU,           /* u */
        S_ISGID | S_IRWXG,           /* g */
        S_IRWXO                      /* o */
    };
    static const mode_t perm_mask[] = {
        S_IRUSR | S_IRGRP | S_IROTH, /* r */
        S_IWUSR | S_IWGRP | S_IWOTH, /* w */
        S_IXUSR | S_IXGRP | S_IXOTH, /* x */
        S_IXUSR | S_IXGRP | S_IXOTH, /* X -- special -- see below */
        S_ISUID | S_ISGID,           /* s */
        S_ISVTX                      /* t */
    };
    static const char who_chars[] ALIGN1 = "augo";
    static const char perm_chars[] ALIGN1 = "rwxXst";
    const char *p;
    mode_t wholist;
    mode_t permlist;
    mode_t new_mode;
    char op;

    if ((unsigned char)(*s - '0') < 8) {
        unsigned long tmp;
        char *e;
        tmp = strtoul(s, &e, 8);

        if (*e || (tmp > 07777U)) { /* Check range and trailing chars. */
            return 0;
        }

        *current_mode = tmp;
        return 1;
    }

    new_mode = *current_mode;

    /* Note: we allow empty clauses, and hence empty modes.
     * We treat an empty mode as no change to perms. */

    while (*s) {  /* Process clauses. */
        if (*s == ',') {  /* We allow empty clauses. */
            ++s;
            continue;
        }

        /* Get a wholist. */
        wholist = 0;
WHO_LIST:
        p = who_chars;

        do {
            if (*p == *s) {
                wholist |= who_mask[(int)(p - who_chars)];

                if (!*++s) {
                    return 0;
                }

                goto WHO_LIST;
            }
        }
        while (*++p);

        do {    /* Process action list. */
            if ((*s != '+') && (*s != '-')) {
                if (*s != '=') {
                    return 0;
                }

                /* Since op is '=', clear all bits corresponding to the
                 * wholist, or all file bits if wholist is empty. */
                permlist = ~FILEMODEBITS;

                if (wholist) {
                    permlist = ~wholist;
                }

                new_mode &= permlist;
            }

            op = *s++;
            /* Check for permcopy. */
            p = who_chars + 1;  /* Skip 'a' entry. */

            do {
                if (*p == *s) {
                    int i = 0;
                    permlist = who_mask[(int)(p - who_chars)]
                               & (S_IRWXU | S_IRWXG | S_IRWXO)
                               & new_mode;

                    do {
                        if (permlist & perm_mask[i]) {
                            permlist |= perm_mask[i];
                        }
                    }
                    while (++i < 3);

                    ++s;
                    goto GOT_ACTION;
                }
            }
            while (*++p);

            /* It was not a permcopy, so get a permlist. */
            permlist = 0;
PERM_LIST:
            p = perm_chars;

            do {
                if (*p == *s) {
                    if ((*p != 'X')
                        || (new_mode & (S_IFDIR | S_IXUSR | S_IXGRP | S_IXOTH))
                       ) {
                        permlist |= perm_mask[(int)(p - perm_chars)];
                    }

                    if (!*++s) {
                        break;
                    }

                    goto PERM_LIST;
                }
            }
            while (*++p);

GOT_ACTION:

            if (permlist) { /* The permlist was nonempty. */
                mode_t tmp = wholist;

                if (!wholist) {
                    mode_t u_mask = umask(0);
                    umask(u_mask);
                    tmp = ~u_mask;
                }

                permlist &= tmp;

                if (op == '-') {
                    new_mode &= ~permlist;
                }
                else {
                    new_mode |= permlist;
                }
            }
        }
        while (*s && (*s != ','));
    }

    *current_mode = new_mode;
    return 1;
}
