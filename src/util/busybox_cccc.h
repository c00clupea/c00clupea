#ifndef BUSY_BOX_CCCC_H
#define BUSY_BOX_CCCC_H
/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 */
/*#if ENABLE_LONG_OPTS || ENABLE_FEATURE_GETOPT_LONG*/
# include <getopt.h>
/*#endif*/
#include <stdio.h>
#include <stdlib.h>
#include "../global.h"
#define type long long

#define FAST_FUNC

typedef signed char smallint;
typedef struct llist_t {
	struct llist_t *link;
	char *data;
} llist_t;
void llist_add_to(llist_t **old_head, void *data) FAST_FUNC;
void llist_add_to_end(llist_t **list_head, void *data) FAST_FUNC;
void *llist_pop(llist_t **elm) FAST_FUNC;
void llist_unlink(llist_t **head, llist_t *elm) FAST_FUNC;
void llist_free(llist_t *elm, void (*freeit)(void *data)) FAST_FUNC;
llist_t *llist_rev(llist_t *list) FAST_FUNC;
llist_t *llist_find_str(llist_t *first, const char *str) FAST_FUNC;
void * xzalloc(size_t size);

uint32_t FAST_FUNC getopt32(char **argv, const char *applet_opts, ...);

#endif
