/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	c00_array_list.c
 * created: 	Thu Sep 11 08:29:53 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */

#include "c00_array_list.h"

int c00_array_list_init(struct c00_array_list *ptr, int max_size)
{
    check(max_size > 1, "max_size too small %d ", max_size);
    ptr->size = max_size;
    ptr->buckets = malloc(max_size * sizeof(void *));

    for(int i = 0; i < max_size; i ++) {
        ptr->buckets[i] = NULL;
    }

    mem_check(ptr->buckets);
    return TRUE;
error:
    return ERROR;
}
int c00_array_list_destroy_free(struct c00_array_list *ptr)
{
    mem_check(ptr);
    mem_check(ptr->buckets);

    for(int i = 0; i < ptr->size; i ++) {
        if(ptr->buckets[i] != NULL) {
            free(ptr->buckets[i]);
        }
    }

    free(ptr->buckets);
    free(ptr);
    return TRUE;
error:

    if(ptr) {
        free(ptr);
    }

    return ERROR;
}

int c00_array_list_destroy(struct c00_array_list *ptr)
{
    mem_check(ptr);
    mem_check(ptr->buckets);
    free(ptr->buckets);
    free(ptr);
    return TRUE;
error:

    if(ptr) {
        free(ptr);
    }

    return ERROR;
}
int c00_array_list_set(struct c00_array_list *ptr, int idx, void *val)
{
    mem_check(ptr);
    mem_check(val);
    check(idx < ptr->size && idx >= 0, "idx out of scope %d", idx);
    ptr->buckets[idx] = NULL;//makes no sense but makes the overwrite clear
    ptr->buckets[idx] = val;
    return TRUE;
error:
    return ERROR;
}
int c00_array_list_remove(struct c00_array_list *ptr, int idx)
{
    mem_check(ptr);
    check(idx < ptr->size && idx >= 0, "idx out of scope %d", idx);
    mem_check(ptr->buckets[idx]);
    ptr->buckets[idx] = NULL;
    return TRUE;
error:
    return ERROR;
}

int c00_array_list_remove_free(struct c00_array_list *ptr, int idx)
{
    mem_check(ptr);
    check(idx < ptr->size && idx >= 0, "idx out of scope %d", idx);
    mem_check(ptr->buckets[idx]);
    free(ptr->buckets[idx]);
    ptr->buckets[idx] = NULL;
    return TRUE;
error:
    return ERROR;
}
int c00_array_list_get(struct c00_array_list *ptr, int idx, void **val)
{
    mem_check(ptr);
    check(idx < ptr->size && idx >= 0, "idx out of scope %d", idx);
    mem_check(ptr->buckets[idx]);
    *val = ptr->buckets[idx];
    mem_check(val);
    return TRUE;
error:
    return ERROR;
}

#ifdef USEC00TESTS


int main(int argc, char *argv[])
{
    HEAD_TEST("Array_LIST");
    struct c00_array_list *list;
    list = malloc(sizeof(struct c00_array_list));
    ASSERT_TEST("init", TRUE, c00_array_list_init(list, 50));
    char *result;
    ASSERT_TEST("get empty", ERROR, c00_array_list_get(list, 22, (void *)&result));
    char *insert = malloc(20 * sizeof(char));
    strcpy(insert, "hallo");
    ASSERT_TEST("insert", TRUE, c00_array_list_set(list, 0, insert));
    ASSERT_TEST("get", TRUE, c00_array_list_get(list, 0, (void *)&result));

    if(strcmp(result, "hallo") == 0) {
        ASSERT_TEST("check_get_equal", TRUE, TRUE);
    }

    ASSERT_TEST("remove_free", TRUE, c00_array_list_remove_free(list, 0));
    insert = malloc(20 * sizeof(char));
    strcpy(insert, "hallo2");
    ASSERT_TEST("insert", TRUE, c00_array_list_set(list, 0, insert));

    if(strcmp(result, "hallo2") == 0) {
        ASSERT_TEST("check_get_equal", TRUE, TRUE);
    }

    ASSERT_TEST("remove", TRUE, c00_array_list_remove(list, 0));
    free(insert);

    for(int i = 0; i < 50; i ++) {
        char *insert2 = malloc(20 * sizeof(char));
        char test[20];
        snprintf(test, 20, "hallo %d", i);
        strcpy(insert2, test);
        c00_array_list_set(list, i, insert2);
    }

    int res = 0;

    for(int i = 0; i < 50; i ++) {
        char *result2;
        c00_array_list_get(list, i, (void *)&result2);
        char test2[20];
        snprintf(test2, 20, "hallo %d", i);

        if(strcmp(result2, test2) == 0) {
            res ++;
        }
    }

    char *result3;
    char insert4[] = "hello world";
    ASSERT_TEST("idx out of bound", ERROR, c00_array_list_get(list, 51, (void *)&result3));
    ASSERT_TEST("idx out of bound", ERROR, c00_array_list_set(list, 51, insert4));
    ASSERT_TEST("many insert and get", 50, res);
    ASSERT_TEST("destroy", TRUE, c00_array_list_destroy_free(list));
}
#endif
