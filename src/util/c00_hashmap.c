#include "c00_hashmap.h"


int _c00_hashmap_test_boundary(struct c00_hashmap *map, int idx);
int _c00_hashmap_get_hash(char *val,unsigned int len);
int _c00_hashmap_calculate_idx_from_hash(int hash, int max_len);
int _c00_hashmap_calculate_idx_from_char(char *val, unsigned int key_len, unsigned int max_len);
int _c00_hashmap_bucket_has_key(struct c00_hashmap_bucket *bucket, char *key);
int _c00_hashmap_has_key_with_bucket(struct c00_hashmap *map, char *key, unsigned int key_len, struct c00_hashmap_bucket **bucket);
int _c00_hashmap_key_insertable(struct c00_hashmap *map, char *key, unsigned int len);
int _c00_hashmap_create_bucket(struct c00_hashmap_bucket *bucket, char *key, unsigned int key_len, char *val);
int _c00_hashmap_null_bucket(struct c00_hashmap_bucket *bucket);
int _c00_hashmap_destroybucketchain(struct c00_hashmap_bucket *bucket);

int _c00_hashmap_null_bucket(struct c00_hashmap_bucket *bucket){
	bucket->next = NULL;
	bucket->key = NULL;
	bucket->val = NULL;
	return TRUE;
}

int _c00_hashmap_test_boundary(struct c00_hashmap *map, int idx){
	
	if(idx > map->max_len - 1){
		return FALSE;
	}

	return TRUE;
}


int c00_hashmap_init(struct c00_hashmap *map, int init_len, int resizable){
	int i;
	i = 0;
	map->max_len = init_len;
	map->actual_fill = 0;
	map->buckets = malloc(map->max_len * sizeof(struct c00_hashmap_bucket));
	
	for(i=0;i<map->max_len;i++){
		_c00_hashmap_null_bucket(&map->buckets[i]);
	}
	
	return TRUE;
}

int _c00_hashmap_destroybucketchain(struct c00_hashmap_bucket *bucket){
	struct c00_hashmap_bucket *tmp;
	struct c00_hashmap_bucket *actual;
	
	actual = bucket;
	while(actual != NULL){

		tmp = actual->next;
		free(actual);
		actual = tmp;
	}
	return TRUE;
}

int c00_hashmap_destroy(struct c00_hashmap *map){
	
	int i;

	for(i = 0; i < map->max_len;i++){
		//C00DEBUG("destroy bucket idx %d",i);
		_c00_hashmap_destroybucketchain(map->buckets[i].next);
	}	

	free(map->buckets);
	free(map);
	return TRUE;	
}

int _c00_hashmap_key_insertable(struct c00_hashmap *map, char *key, unsigned int key_len){
	if(c00_hashmap_has_key(map,key,key_len) == TRUE){
		return FALSE;
	}

	if(map->actual_fill + 1 >= map->max_len){
		return FALSE;
	}
	return TRUE;
}

int _c00_hashmap_create_bucket(struct c00_hashmap_bucket *bucket, char *key, unsigned int key_len, char *val){
	char *new_key = malloc((key_len + 1)*sizeof(char));
	
	strncpy(new_key,key,key_len +1);
	bucket->key = new_key;
	bucket->val = val;
	bucket->next = NULL;
	C00DEBUG("bucket %s:%s",bucket->key,bucket->val);
	return TRUE;
}

int _c00_hashmap_add_bucket_to_idx(struct c00_hashmap *map, struct c00_hashmap_bucket *bucket, unsigned int idx){
	
	struct c00_hashmap_bucket *the_next;

	the_next = &map->buckets[idx];

	while(the_next->next != NULL){
		the_next = the_next->next;
	}
	the_next->next = bucket;

	return TRUE;
}

int c00_hashmap_add_key_value(struct c00_hashmap *map, char *key, int key_len, char *val){
	if(_c00_hashmap_key_insertable(map,key,key_len) != TRUE){
		return FALSE;
	}

	unsigned int idx = _c00_hashmap_calculate_idx_from_char(key,key_len,map->max_len);
	
	struct c00_hashmap_bucket *bucket;
	bucket = malloc(sizeof(struct c00_hashmap_bucket));
	if(_c00_hashmap_create_bucket(bucket, key, key_len, val) != TRUE){
		return FALSE;
	}	

#ifdef WRITEC00CRAP
if(bucket == NULL){
	C00DEBUG("bucket isn null %d",1);
}		
#endif

	if(_c00_hashmap_add_bucket_to_idx(map,bucket,idx) != TRUE){
		return FALSE;
	}
	
	return TRUE;
}



int _c00_hashmap_bucket_has_key(struct c00_hashmap_bucket *bucket, char *key){
	if(strcmp(bucket->key,key) == 0){
		C00DEBUG("bucket test key %s",key);
		return TRUE;
	}
	return FALSE;
}

int c00_hashmap_has_key(struct c00_hashmap *map, char *key, unsigned int key_len){
	struct c00_hashmap_bucket **bucket = malloc(sizeof(struct c00_hashmap_bucket *));
	int result;
	result = _c00_hashmap_has_key_with_bucket(map,key,key_len,bucket);
	free(bucket);
	return result;
}

int _c00_hashmap_has_key_with_bucket(struct c00_hashmap *map, char *key, unsigned int key_len, struct c00_hashmap_bucket **bucket){
	int idx;

	idx = _c00_hashmap_calculate_idx_from_char(key,key_len,map->max_len);


	if(map->buckets[idx].next == NULL){
		C00DEBUG("return %d",FALSE);
		return FALSE; // shortcut
	}

	struct c00_hashmap_bucket *the_next;
	
	the_next = map->buckets[idx].next;
	while(the_next != NULL){
       	       	
		if(_c00_hashmap_bucket_has_key(the_next, key) == TRUE){

			*bucket = the_next;
			C00DEBUG("set bucket for return %d",idx);
			return TRUE;
		}
	        the_next = the_next->next;
	}

	return FALSE;
}
int c00_hashmap_remove_key(struct c00_hashmap *map, char *key, int key_len){
	return 0;
}
int c00_hashmap_get_value(struct c00_hashmap *map, char *key, int key_len, char *val){
	
	struct c00_hashmap_bucket *bucket = malloc(sizeof(struct c00_hashmap_bucket *));
	
	if(_c00_hashmap_has_key_with_bucket(map,key,key_len,&bucket) != TRUE){
		return FALSE;
	}
	
	C00DEBUG("bucket for get found, set val for key %s with val %s",key,bucket->val);
	
	val = bucket->val;		
	return TRUE;
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


#ifdef USEC00TESTS

int _write_and_read_value(struct c00_hashmap *map, char *key, unsigned int len){
	ASSERT_TEST("test insert",TRUE,c00_hashmap_add_key_value(map,key,len,key))
	char *result;
	result = malloc(40 * sizeof(char));

	ASSERT_TEST("test value",TRUE,c00_hashmap_get_value(map,key,len,result))
	if(strcmp(result,"value") == 0){
			ASSERT_TEST("cmp value",TRUE,TRUE)
	}
	free(result);
	return TRUE;
}

int main(int argc, char *argv[]){
	HEAD_TEST("Hashmap");

	struct c00_hashmap *map;
	map = malloc(sizeof(struct c00_hashmap));

	HEAD_TEST("init");
	ASSERT_TEST("init",TRUE,c00_hashmap_init(map,1000,0))
	HEAD_TEST("empyt get");
	ASSERT_TEST("test empty get",FALSE,c00_hashmap_has_key(map,"hallo welt",11))
	HEAD_TEST("insert test");
	ASSERT_TEST("test insert",TRUE,c00_hashmap_add_key_value(map,"hallo welt",11,"value"))	
	HEAD_TEST("get");
	ASSERT_TEST("test existing get",TRUE,c00_hashmap_has_key(map,"hallo welt",11))

       	HEAD_TEST("get value");
	char *result;
	result = malloc(40 * sizeof(char));

	ASSERT_TEST("test value",TRUE,c00_hashmap_get_value(map,"hallo welt",11,result))

		if(strcmp(result,"value") == 0){
			ASSERT_TEST("cmp value",TRUE,TRUE)
		}
	
	HEAD_TEST("set and get many values");
	
	_write_and_read_value(map,"key 1", 5);
	_write_and_read_value(map,"key 2", 5);
	_write_and_read_value(map,"key 3", 5);
	_write_and_read_value(map,"key 4", 5);
	_write_and_read_value(map,"key 5", 5);
	_write_and_read_value(map,"key 6", 5);
	_write_and_read_value(map,"key 7", 5);
	_write_and_read_value(map,"key 8", 5);	

	HEAD_TEST("destroy map");
	ASSERT_TEST("destroy",TRUE,c00_hashmap_destroy(map));

	free(result);
	return 1;
}



#endif
