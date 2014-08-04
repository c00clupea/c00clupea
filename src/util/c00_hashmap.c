#include "c00_hashmap.h"


int _c00_hashmap_test_boundary(struct c00_hashmap *map, int idx);
int _c00_hashmap_get_hash(char *val,unsigned int len);
int _c00_hashmap_calculate_idx_from_hash(int hash, int max_len);
int _c00_hashmap_calculate_idx_from_char(char *val, unsigned int key_len, unsigned int max_len);

int _c00_hashmap_test_boundary(struct c00_hashmap *map, int idx){
	
	if(idx > map->max_len - 1){
		return FALSE;
	}

	return TRUE;
}


int c00_hashmap_init(struct c00_hashmap *map, int init_len, int resizable){
	
	map->max_len = init_len;
	map->actual_fill = 0;
	map->buckets = malloc(map->max_len * sizeof(c00_hashmap_bucket));
	
	return 0;
}

int c00_hashmap_destroy(struct c00_hashmap *map){
	free(map->buckets);
	free(map);
	
}

int c00_hashmap_add_key_value(struct c00_hashmap *map, char *key, int key_len, void *val){
	return 0;
}
int c00_hashmap_has_key(struct c00_hashmap *map, char *key, unsigned int key_len){
	
	int idx;

	idx = _c00_hashmap_calculate_idx_from_char(key,key_len,map->max_len);

	if(map->buckets[idx] == NULL){
		return FALSE; // shortcut
	}

	return FALSE;
}
int c00_hashmap_remove_key(struct c00_hashmap *map, char *key, int key_len){
	return 0;
}
int c00_hashmap_get_value(struct c00_hashmap *map, char *key, int key_len, void *val){
	return 0;
}

int _c00_hashmap_calculate_idx_from_hash(int hash, int max_len){
	if(hash < 0 || max_len < 1){
		return -1;
	}

	return hash % max_len;
}

int _c00_hashmap_calculate_idx_from_char(char *key, unsigned int key_len, unsigned int max_len){
	int hash, idx;

	hash = _c00_hashmap_get_hash(key,key_len);
	idx = _c00_hashmap_calculate_idx_from_hash(hash,max_len);

	return idx;

}


int _c00_hashmap_get_hash(char *val,unsigned int len){
   	//This is just the standard ELF-Hash as proposed in many books, blogs, and so on
	unsigned int hash = 0;
   	unsigned int x    = 0;
   	unsigned int i    = 0;
	char *str      	  = val;
	
   	for(i = 0; i < len; str++, i++)
   	{
      		hash = (hash << 4) + (*str);
      		if((x = hash & 0xF0000000L) != 0)
      		{
         		hash ^= (x >> 24);
      		}
      		hash &= ~x;
   	}

   return hash;


}
