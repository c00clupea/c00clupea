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
 **/
/* vi: set sw=4 ts=4: */
/*
 * universal getopt32 implementation for busybox
 *
 * Copyright (C) 2003-2005  Vladimir Oleynik  <dzo@simtreas.ru>
 *
 * Licensed under GPLv2 or later, see file LICENSE in this source tree.
 */

/*#if ENABLE_LONG_OPTS || ENABLE_FEATURE_GETOPT_LONG*/
# include <getopt.h>
/*#endif*/
#include <stdio.h>
#include <stdlib.h>
#include "../global.h"
#define type long long

#define FAST_FUNC
/*#include "libbb.h"*/
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


void* FAST_FUNC xzalloc(size_t size)
{
	void *ptr = malloc(size);
	memset(ptr, 0, size);
	return ptr;
}

/* Add data to the start of the linked list.  */
void FAST_FUNC llist_add_to(llist_t **old_head, void *data)
{
	llist_t *new_head = malloc(sizeof(llist_t));

	new_head->data = data;
	new_head->link = *old_head;
	*old_head = new_head;
}

/* Add data to the end of the linked list.  */
void FAST_FUNC llist_add_to_end(llist_t **list_head, void *data)
{
	while (*list_head)
		list_head = &(*list_head)->link;
	*list_head = xzalloc(sizeof(llist_t));
	(*list_head)->data = data;
	/*(*list_head)->link = NULL;*/
}

/* Remove first element from the list and return it */
void* FAST_FUNC llist_pop(llist_t **head)
{
	void *data = NULL;
	llist_t *temp = *head;

	if (temp) {
		data = temp->data;
		*head = temp->link;
		free(temp);
	}
	return data;
}

/* Unlink arbitrary given element from the list */
void FAST_FUNC llist_unlink(llist_t **head, llist_t *elm)
{
	if (!elm)
		return;
	while (*head) {
		if (*head == elm) {
			*head = (*head)->link;
			break;
		}
		head = &(*head)->link;
	}
}

/* Recursively free all elements in the linked list.  If freeit != NULL
 * call it on each datum in the list */
void FAST_FUNC llist_free(llist_t *elm, void (*freeit)(void *data))
{
	while (elm) {
		void *data = llist_pop(&elm);

		if (freeit)
			freeit(data);
	}
}

/* Reverse list order. */
llist_t* FAST_FUNC llist_rev(llist_t *list)
{
	llist_t *rev = NULL;

	while (list) {
		llist_t *next = list->link;

		list->link = rev;
		rev = list;
		list = next;
	}
	return rev;
}

llist_t* FAST_FUNC llist_find_str(llist_t *list, const char *str)
{
	while (list) {
		if (strcmp(list->data, str) == 0)
			break;
		list = list->link;
	}
	return list;
}





/**#####################
 * This is a bloody Hack
 **#####################
 *  This inline blah is the excerpt of a few hundred lines in busybox....
 *  However the busybox is really "nice" it is written to solve hundreds of problems...
 *  But is is some pain to read it...
 * <*))><
 */
static unsigned type xatoi_positive(const char *cstr){
	unsigned type r;
	char *e;
	r = strtoull(cstr,&e,10);
	if(r <= INT_MAX){
		return r;
	}
	exit(0);//Simulates the real behavior
}


/* Code here assumes that 'unsigned' is at least 32 bits wide */

const char *const bb_argv_dash[] = { "-", NULL };

const char *opt_complementary;

enum {
	PARAM_STRING,
	PARAM_LIST,
	PARAM_INT,
};

typedef struct {
	unsigned char opt_char;
	smallint param_type;
	unsigned switch_on;
	unsigned switch_off;
	unsigned incongruously;
	unsigned requires;
	void **optarg;  /* char**, llist_t** or int *. */
	int *counter;
} t_complementary;

/* You can set applet_long_options for parse called long options */
#if ENABLE_LONG_OPTS || ENABLE_FEATURE_GETOPT_LONG
static const struct option bb_null_long_options[1] = {
	{ 0, 0, 0, 0 }
};
const char *applet_long_options;
#endif

uint32_t option_mask32;

uint32_t FAST_FUNC
getopt32(char **argv, const char *applet_opts, ...)
{
	int argc;
	unsigned flags = 0;
	unsigned requires = 0;
	t_complementary complementary[33]; /* last stays zero-filled */
	char first_char;
	int c;
	const unsigned char *s;
	t_complementary *on_off;
	va_list p;
#if ENABLE_LONG_OPTS || ENABLE_FEATURE_GETOPT_LONG
	const struct option *l_o;
	struct option *long_options = (struct option *) &bb_null_long_options;
#endif
	unsigned trigger;
	char **pargv;
	int min_arg = 0;
	int max_arg = -1;

#define SHOW_USAGE_IF_ERROR     1
#define ALL_ARGV_IS_OPTS        2
#define FIRST_ARGV_IS_OPT       4

	int spec_flgs = 0;

	/* skip 0: some applets cheat: they do not actually HAVE argv[0] */
	argc = 1;
	while (argv[argc])
		argc++;

	va_start(p, applet_opts);

	c = 0;
	on_off = complementary;
	memset(on_off, 0, sizeof(complementary));

	/* skip bbox extension */
	first_char = applet_opts[0];
	if (first_char == '!')
		applet_opts++;

	/* skip GNU extension */
	s = (const unsigned char *)applet_opts;
	if (*s == '+' || *s == '-')
		s++;
	while (*s) {
		if (c >= 32)
			break;
		on_off->opt_char = *s;
		on_off->switch_on = (1 << c);
		if (*++s == ':') {
			on_off->optarg = va_arg(p, void **);
			while (*++s == ':')
				continue;
		}
		on_off++;
		c++;
	}

#if ENABLE_LONG_OPTS || ENABLE_FEATURE_GETOPT_LONG
	if (applet_long_options) {
		const char *optstr;
		unsigned i, count;

		count = 1;
		optstr = applet_long_options;
		while (optstr[0]) {
			optstr += strlen(optstr) + 3; /* skip NUL, has_arg, val */
			count++;
		}
		/* count == no. of longopts + 1 */
		long_options = alloca(count * sizeof(*long_options));
		memset(long_options, 0, count * sizeof(*long_options));
		i = 0;
		optstr = applet_long_options;
		while (--count) {
			long_options[i].name = optstr;
			optstr += strlen(optstr) + 1;
			long_options[i].has_arg = (unsigned char)(*optstr++);
			/* long_options[i].flag = NULL; */
			long_options[i].val = (unsigned char)(*optstr++);
			i++;
		}
		for (l_o = long_options; l_o->name; l_o++) {
			if (l_o->flag)
				continue;
			for (on_off = complementary; on_off->opt_char; on_off++)
				if (on_off->opt_char == l_o->val)
					goto next_long;
			if (c >= 32)
				break;
			on_off->opt_char = l_o->val;
			on_off->switch_on = (1 << c);
			if (l_o->has_arg != no_argument)
				on_off->optarg = va_arg(p, void **);
			c++;
 next_long: ;
		}
		/* Make it unnecessary to clear applet_long_options
		 * by hand after each call to getopt32
		 */
		applet_long_options = NULL;
	}
#endif /* ENABLE_LONG_OPTS || ENABLE_FEATURE_GETOPT_LONG */
	for (s = (const unsigned char *)opt_complementary; s && *s; s++) {
		t_complementary *pair;
		unsigned *pair_switch;

		if (*s == ':')
			continue;
		c = s[1];
		if (*s == '?') {
			if (c < '0' || c > '9') {
				spec_flgs |= SHOW_USAGE_IF_ERROR;
			} else {
				max_arg = c - '0';
				s++;
			}
			continue;
		}
		if (*s == '-') {
			if (c < '0' || c > '9') {
				if (c == '-') {
					spec_flgs |= FIRST_ARGV_IS_OPT;
					s++;
				} else
					spec_flgs |= ALL_ARGV_IS_OPTS;
			} else {
				min_arg = c - '0';
				s++;
			}
			continue;
		}
		if (*s == '=') {
			min_arg = max_arg = c - '0';
			s++;
			continue;
		}
		for (on_off = complementary; on_off->opt_char; on_off++)
			if (on_off->opt_char == *s)
				goto found_opt;
		/* Without this, diagnostic of such bugs is not easy */
		//bb_error_msg_and_die("NO OPT %c!", *s);
		printf("NO OPT %c!", *s);
		exit(1);
 found_opt:
		if (c == ':' && s[2] == ':') {
			on_off->param_type = PARAM_LIST;
			continue;
		}
		if (c == '+' && (s[2] == ':' || s[2] == '\0')) {
			on_off->param_type = PARAM_INT;
			s++;
			continue;
		}
		if (c == ':' || c == '\0') {
			requires |= on_off->switch_on;
			continue;
		}
		if (c == '-' && (s[2] == ':' || s[2] == '\0')) {
			flags |= on_off->switch_on;
			on_off->incongruously |= on_off->switch_on;
			s++;
			continue;
		}
		if (c == *s) {
			on_off->counter = va_arg(p, int *);
			s++;
		}
		pair = on_off;
		pair_switch = &pair->switch_on;
		for (s++; *s && *s != ':'; s++) {
			if (*s == '?') {
				pair_switch = &pair->requires;
			} else if (*s == '-') {
				if (pair_switch == &pair->switch_off)
					pair_switch = &pair->incongruously;
				else
					pair_switch = &pair->switch_off;
			} else {
				for (on_off = complementary; on_off->opt_char; on_off++)
					if (on_off->opt_char == *s) {
						*pair_switch |= on_off->switch_on;
						break;
					}
			}
		}
		s--;
	}
	opt_complementary = NULL;
	va_end(p);

	if (spec_flgs & (FIRST_ARGV_IS_OPT | ALL_ARGV_IS_OPTS)) {
		pargv = argv + 1;
		while (*pargv) {
			if (pargv[0][0] != '-' && pargv[0][0] != '\0') {
				/* Can't use alloca: opts with params will
				 * return pointers to stack!
				 * NB: we leak these allocations... */
				char *pp = malloc(strlen(*pargv) + 2);
				*pp = '-';
				strcpy(pp + 1, *pargv);
				*pargv = pp;
			}
			if (!(spec_flgs & ALL_ARGV_IS_OPTS))
				break;
			pargv++;
		}
	}

	/* In case getopt32 was already called:
	 * reset the libc getopt() function, which keeps internal state.
	 * run_nofork_applet() does this, but we might end up here
	 * also via gunzip_main() -> gzip_main(). Play safe.
	 */
#ifdef __GLIBC__
	optind = 0;
#else /* BSD style */
	optind = 1;
	/* optreset = 1; */
#endif
	/* optarg = NULL; opterr = 0; optopt = 0; - do we need this?? */

	/* Note: just "getopt() <= 0" will not work well for
	 * "fake" short options, like this one:
	 * wget $'-\203' "Test: test" http://kernel.org/
	 * (supposed to act as --header, but doesn't) */
#if ENABLE_LONG_OPTS || ENABLE_FEATURE_GETOPT_LONG
	while ((c = getopt_long(argc, argv, applet_opts,
			long_options, NULL)) != -1) {
#else
	while ((c = getopt(argc, argv, applet_opts)) != -1) {
#endif
		/* getopt prints "option requires an argument -- X"
		 * and returns '?' if an option has no arg, but one is reqd */
		c &= 0xff; /* fight libc's sign extension */
		for (on_off = complementary; on_off->opt_char != c; on_off++) {
			/* c can be NUL if long opt has non-NULL ->flag,
			 * but we construct long opts so that flag
			 * is always NULL (see above) */
			if (on_off->opt_char == '\0' /* && c != '\0' */) {
				/* c is probably '?' - "bad option" */
				goto error;
			}
		}
		if (flags & on_off->incongruously)
			goto error;
		trigger = on_off->switch_on & on_off->switch_off;
		flags &= ~(on_off->switch_off ^ trigger);
		flags |= on_off->switch_on ^ trigger;
		flags ^= trigger;
		if (on_off->counter)
			(*(on_off->counter))++;
		if (optarg) {
			if (on_off->param_type == PARAM_LIST) {
				llist_add_to_end((llist_t **)(on_off->optarg), optarg);
			} else if (on_off->param_type == PARAM_INT) {
/**#####################
 * This is a bloody Hack
 **#####################
 *  xatoi_positive is built in the xatonum_template.c from busybox
 *  However this xatonum is really bad
 *  Hence we do not want to rebuild busybox, just to check wether a integer is positive or not....
 *  This xatoi blah is rebuilt with a simple inline method....
 * <*))><
 */
//TODO: xatoi_positive indirectly pulls in printf machinery
				*(unsigned*)(on_off->optarg) = xatoi_positive(optarg);
			} else if (on_off->optarg) {
				*(char **)(on_off->optarg) = optarg;
			}
		}
	}

	/* check depending requires for given options */
	for (on_off = complementary; on_off->opt_char; on_off++) {
		if (on_off->requires
		 && (flags & on_off->switch_on)
		 && (flags & on_off->requires) == 0
		) {
			goto error;
		}
	}
	if (requires && (flags & requires) == 0)
		goto error;
	argc -= optind;
	if (argc < min_arg || (max_arg >= 0 && argc > max_arg))
		goto error;

	option_mask32 = flags;
	return flags;

 error:
	if (first_char != '!')
		//bb_show_usage();
		printf("No help available!\n");
	return (int32_t)-1;
}
