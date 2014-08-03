#ifndef C00_HASHMAP_H
#define C00_HASHMAP_H
#include "../global.h"



struct c00_hashmap{
	
};

struct c00_hashmap_bucket{

};

int c00_hashmap_init(struct c00_hashmap *map, int init_len, int resizable);

int c00_hashmap_add_key_value(struct c00_hashmap *map, char *key, int key_len, void *val);
int c00_hashmap_has_key(struct c00_hashmap *map, char *key, int key_len);
int c00_hashmap_remove_key(struct c00_hashmap *map, char *key, int key_len);
int c00_hashmap_get_value(struct c00_hashmap *map, char *key, int key_len, void *val);




#endif
