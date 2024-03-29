/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	c00_hashmap.c
 * created: 	Thu Sep 11 08:31:40 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */

#include "c00_hashmap.h"


/**static int _c00_hashmap_test_boundary(struct c00_hashmap *map, int idx);**/
static int _c00_hashmap_get_hash(char *val, unsigned int len);
static int _c00_hashmap_calculate_idx_from_hash(int hash, int max_len);
static int _c00_hashmap_calculate_idx_from_char(char *val, unsigned int key_len, unsigned int max_len);
static int _c00_hashmap_bucket_has_key(struct c00_hashmap_bucket *bucket, char *key);
static int _c00_hashmap_has_key_with_bucket(struct c00_hashmap *map, char *key, unsigned int key_len, struct c00_hashmap_bucket **bucket);
static int _c00_hashmap_key_insertable(struct c00_hashmap *map, char *key, unsigned int len);
static int _c00_hashmap_create_bucket(struct c00_hashmap_bucket *bucket, char *key, unsigned int key_len, void *val);
static int _c00_hashmap_null_bucket(struct c00_hashmap_bucket *bucket);
static int _c00_hashmap_destroybucketchain(struct c00_hashmap_bucket *bucket);

int _c00_hashmap_null_bucket(struct c00_hashmap_bucket *bucket)
{
    bucket->next = NULL;
    bucket->key = NULL;
    bucket->val = NULL;
    return TRUE;
}

/**int _c00_hashmap_test_boundary(struct c00_hashmap *map, int idx){

	if(idx > map->max_len - 1){
		return FALSE;
	}

	return TRUE;
	}**/


int c00_hashmap_init(struct c00_hashmap *map, int init_len)
{
    int i;
    map->max_len = init_len;
    map->actual_fill = 0;
    map->buckets = malloc(map->max_len * sizeof(struct c00_hashmap_bucket));

    for(i = 0; i < map->max_len; i++) {
        _c00_hashmap_null_bucket(&map->buckets[i]);
    }

    return TRUE;
}

int _c00_hashmap_destroybucketchain(struct c00_hashmap_bucket *bucket)
{
    struct c00_hashmap_bucket *tmp;
    struct c00_hashmap_bucket *actual;
    actual = bucket;

    while(actual != NULL) {
        tmp = actual->next;
        free(actual);
        actual = tmp;
    }

    return TRUE;
}

int c00_hashmap_destroy(struct c00_hashmap *map)
{
    int i;

    for(i = 0; i < map->max_len; i++) {
        //C00DEBUG("destroy bucket idx %d",i);
        _c00_hashmap_destroybucketchain(map->buckets[i].next);
    }

    free(map->buckets);
    free(map);
    return TRUE;
}

int _c00_hashmap_key_insertable(struct c00_hashmap *map, char *key, unsigned int key_len)
{
    if(c00_hashmap_has_key(map, key, key_len) == TRUE) {
        return FALSE;
    }

    if(map->actual_fill + 1 >= map->max_len) {
        return FALSE;
    }

    return TRUE;
}

int _c00_hashmap_create_bucket(struct c00_hashmap_bucket *bucket, char *key, unsigned int key_len, void *val)
{
    char *new_key = malloc((key_len + 1) * sizeof(char));
    strncpy(new_key, key, key_len + 1);
    bucket->key = new_key;
    bucket->val = val;
    bucket->next = NULL;
    C00DEBUG("bucket %s", bucket->key);
    return TRUE;
}

int _c00_hashmap_add_bucket_to_idx(struct c00_hashmap *map, struct c00_hashmap_bucket *bucket, unsigned int idx)
{
    struct c00_hashmap_bucket *the_next;
    the_next = &map->buckets[idx];

    while(the_next->next != NULL) {
        the_next = the_next->next;
    }

    the_next->next = bucket;
    return TRUE;
}

int c00_hashmap_add_key_value(struct c00_hashmap *map, char *key, int key_len, void *val)
{
    if(_c00_hashmap_key_insertable(map, key, key_len) != TRUE) {
        return FALSE;
    }

    unsigned int idx = _c00_hashmap_calculate_idx_from_char(key, key_len, map->max_len);
    struct c00_hashmap_bucket *bucket;
    bucket = malloc(sizeof(struct c00_hashmap_bucket));

    if(_c00_hashmap_create_bucket(bucket, key, key_len, val) != TRUE) {
        return FALSE;
    }

#ifdef WRITEC00CRAP

    if(bucket == NULL) {
        C00DEBUG("bucket isn null %d", 1);
    }

#endif

    if(_c00_hashmap_add_bucket_to_idx(map, bucket, idx) != TRUE) {
        return FALSE;
    }

    return TRUE;
}



int _c00_hashmap_bucket_has_key(struct c00_hashmap_bucket *bucket, char *key)
{
    if(strcmp(bucket->key, key) == 0) {
        C00DEBUG("bucket test key %s", key);
        return TRUE;
    }

    return FALSE;
}

int c00_hashmap_has_key(struct c00_hashmap *map, char *key, unsigned int key_len)
{
    struct c00_hashmap_bucket *bucket;
    int result;
    result = _c00_hashmap_has_key_with_bucket(map, key, key_len, &bucket);
    return result;
}

int _c00_hashmap_has_key_with_bucket(struct c00_hashmap *map, char *key, unsigned int key_len, struct c00_hashmap_bucket **bucket)
{
    int idx;
    idx = _c00_hashmap_calculate_idx_from_char(key, key_len, map->max_len);

    if(map->buckets[idx].next == NULL) {
        C00DEBUG("return %d", FALSE);
        return FALSE; // shortcut
    }

    struct c00_hashmap_bucket *the_next;

    the_next = map->buckets[idx].next;

    while(the_next != NULL) {
        if(_c00_hashmap_bucket_has_key(the_next, key) == TRUE) {
            *bucket = the_next;
            C00DEBUG("set bucket for return %d", idx);
            return TRUE;
        }

        the_next = the_next->next;
    }

    return FALSE;
}
int c00_hashmap_remove_key(struct c00_hashmap *map, char *key, int key_len)
{
    C00DEBUG("try to remove mal with %d %s, %d", map->actual_fill, key, key_len);
    syslog(LOG_ERR, "try to remove mal with %d %s, %d --> NOT IMPLEMENTED", map->actual_fill, key, key_len);
    return 0;
}
int c00_hashmap_get_value(struct c00_hashmap *map, char *key, int key_len, void **val)
{
    struct c00_hashmap_bucket *bucket;

    if(_c00_hashmap_has_key_with_bucket(map, key, key_len, &bucket) != TRUE) {
        C00DEBUG("sry %s not found in hashmap", key);
        return FALSE;
    }

    C00DEBUG("bucket for get found, set val for key %s with val %s", key, bucket->val);
    *val = bucket->val;
    return TRUE;
}

int _c00_hashmap_calculate_idx_from_hash(int hash, int max_len)
{
    if(hash < 0 || max_len < 1) {
        return -1;
    }

    return hash % max_len;
}

int _c00_hashmap_calculate_idx_from_char(char *key, unsigned int key_len, unsigned int max_len)
{
    int hash, idx;
    C00DEBUG("IDX for %s,len %d, max_len %d", key, key_len, max_len);
    hash = _c00_hashmap_get_hash(key, key_len);
    idx = _c00_hashmap_calculate_idx_from_hash(hash, max_len);
    return idx;
}


int _c00_hashmap_get_hash(char *val, unsigned int len)
{
    //This is just the standard ELF-Hash as proposed in many books, blogs, and so on
    unsigned int hash = 0;
    unsigned int x    = 0;
    unsigned int i    = 0;
    char *str      	  = val;

    for(i = 0; i < len && *str != '\0'; str++, i++) {
        hash = (hash << 4) + (*str);

        if((x = hash & 0xF0000000L) != 0) {
            hash ^= (x >> 24);
        }

        hash &= ~x;
    }

    return hash;
}


#ifdef USEC00TESTS

static int _write_and_read_value(struct c00_hashmap *map, char *key, unsigned int len)
{
    ASSERT_TEST("test insert", TRUE, c00_hashmap_add_key_value(map, key, len, key))
    char *result;
    ASSERT_TEST("test value", TRUE, c00_hashmap_get_value(map, key, len, (void *)&result))

    if(strcmp(result, "value") == 0) {
        ASSERT_TEST("cmp value", TRUE, TRUE)
    }

    return TRUE;
}

int main(int argc, char *argv[])
{
    HEAD_TEST("Hashmap");
    struct c00_hashmap *map;
    map = malloc(sizeof(struct c00_hashmap));
    ASSERT_TEST("init", TRUE, c00_hashmap_init(map, 1000))
    ASSERT_TEST("test empty get", FALSE, c00_hashmap_has_key(map, "hallo welt", 11))
    ASSERT_TEST("test insert", TRUE, c00_hashmap_add_key_value(map, "hallo welt", 11, "value"))
    ASSERT_TEST("test existing get", TRUE, c00_hashmap_has_key(map, "hallo welt", 11))
    char *result;
    ASSERT_TEST("test value", TRUE, c00_hashmap_get_value(map, "hallo welt", 11, (void *)&result))

    if(strcmp(result, "value") == 0) {
        ASSERT_TEST("cmp value", TRUE, TRUE)
    }

    _write_and_read_value(map, "key 1", 5);
    _write_and_read_value(map, "key 2", 5);
    _write_and_read_value(map, "key 3", 5);
    _write_and_read_value(map, "key 4", 5);
    _write_and_read_value(map, "key 5", 5);
    _write_and_read_value(map, "key 6", 5);
    _write_and_read_value(map, "key 7", 5);
    _write_and_read_value(map, "key 8", 5);
    ASSERT_TEST("destroy", TRUE, c00_hashmap_destroy(map));
    return 1;
}



#endif
