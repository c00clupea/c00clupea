/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	c00_linked_list.h
 * created: 	Thu Sep 11 08:32:11 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */

#ifndef C00_LINKED_LIST_H
#define C00_LINKED_LIST_H
#include "../global.h"
#include <stdio.h>
#include <string.h>



struct c00_linked_list {
    int size;
    struct c00_linked_list_bucket *first;
    struct c00_linked_list_bucket *last;
    struct c00_linked_list_bucket *actual;
    int idx;
};

struct c00_linked_list_bucket {
    struct c00_linked_list_bucket *left;
    struct c00_linked_list_bucket *right;
    void *val;
};

int c00_linked_list_init(struct c00_linked_list *ptr);
int c00_linked_list_destroy(struct c00_linked_list *ptr);
int c00_linked_list_destroy_free(struct c00_linked_list *ptr);
int c00_linked_list_push_end(struct c00_linked_list *ptr, void *val);
int c00_linked_list_push_start(struct c00_linked_list *ptr, void *val);
int c00_linked_list_pop_end(struct c00_linked_list *ptr, void **val);
int c00_linked_list_pop_start(struct c00_linked_list *ptr, void **val);
/**int c00_linked_list_set(struct c00_linked_list *ptr,int idx, void *val);
int c00_linked_list_get(struct c00_linked_list *ptr,int idx, void **val);
int c00_linked_list_remove(struct c00_linked_list *ptr, int idx);**/
int c00_linked_list_imove(struct c00_linked_list *ptr, signed int range);
/**i... means index on the current index (move with imove) this action will be done**/
int c00_linked_list_iget(struct c00_linked_list *ptr, void **val);
int c00_linked_list_iset(struct c00_linked_list *ptr, void *val);
int c00_linked_list_iremove(struct c00_linked_list *ptr, void **val);
int c00_linked_list_destroy_dlg_free(struct c00_linked_list *ptr, int (*dtor)(void *));

#endif
