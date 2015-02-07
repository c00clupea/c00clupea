/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	c00_hashmap.h
 * created: 	Thu Sep 11 08:31:51 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */


#ifndef C00_HASHMAP_H
#define C00_HASHMAP_H
#include "../global.h"
#include <stdio.h>
#include <string.h>


struct c00_hashmap {

    int 				max_len;
    int 				actual_fill;
    struct c00_hashmap_bucket 	*buckets;

};

struct c00_hashmap_bucket {
    int	is_first;
    struct c00_hashmap_bucket *next;
    char *key;
    void *val;

};


int c00_hashmap_init(struct c00_hashmap *map, int init_len);
int c00_hashmap_add_key_value(struct c00_hashmap *map, char *key, int key_len, void *val);
int c00_hashmap_has_key(struct c00_hashmap *map, char *key, unsigned int key_len);
int c00_hashmap_remove_key(struct c00_hashmap *map, char *key, int key_len);
int c00_hashmap_get_value(struct c00_hashmap *map, char *key, int key_len, void **val);
int c00_hashmap_destroy(struct c00_hashmap *map);



#endif
