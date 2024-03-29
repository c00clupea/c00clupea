/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	c00_array_list.h
 * created: 	Thu Sep 11 08:29:24 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */

#ifndef C00_ARRAYLIST_H
#define C00_ARRAYLIST_H
#include "../global.h"
#include <stdio.h>
#include <string.h>

struct c00_array_list {
    int size;
    void **buckets;
};

int c00_array_list_init(struct c00_array_list *ptr, int max_size);
int c00_array_list_destroy(struct c00_array_list *ptr);
int c00_array_list_destroy_free(struct c00_array_list *ptr);
int c00_array_list_set(struct c00_array_list *ptr, int idx, void *val);
int c00_array_list_remove(struct c00_array_list *ptr, int idx);
int c00_array_list_remove_free(struct c00_array_list *ptr, int idx);
int c00_array_list_get(struct c00_array_list *ptr, int idx, void **val);
#endif
