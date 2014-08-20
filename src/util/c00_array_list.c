#include "c00_array_list.h"

int c00_array_list_init(struct c00_array_list *ptr, int max_size){
	check(max_size > 1,"max_size too small %d ",max_size);
	ptr->size = max_size;
	ptr->buckets = malloc(max_size * sizeof(void *));
	for(int i = 0; i < max_size; i ++){
		ptr->buckets[i] = NULL;
	}
	mem_check(ptr->buckets);
	return TRUE;
error:
	return ERROR;
}
int c00_array_list_destroy_free(struct c00_array_list *ptr){
	mem_check(ptr);
	mem_check(ptr->buckets);

	for(int i = 0; i < ptr->size; i ++){
		if(ptr->buckets[i] != NULL){
			C00REACH(i);
			free(ptr->buckets[i]);
		}
	}	
	
	free(ptr->buckets);
	free(ptr);
	return TRUE;
error:
	if(ptr){
		free(ptr);
	}
	return ERROR;
}

int c00_array_list_destroy(struct c00_array_list *ptr){
	mem_check(ptr);
	mem_check(ptr->buckets);		
	free(ptr->buckets);
	free(ptr);
	return TRUE;
error:
	if(ptr){
		free(ptr);
	}
	return ERROR;
}
int c00_array_list_set(struct c00_array_list *ptr, int idx, void *val){
	mem_check(ptr);
	mem_check(val);
	check(idx < ptr->size && idx >= 0,"idx out of scope %d",idx);
	ptr->buckets[idx] = NULL;//makes no sense but makes the overwrite clear
	ptr->buckets[idx] = val;
	return TRUE;
error:
	return ERROR;
}
int c00_array_list_remove(struct c00_array_list *ptr, int idx){
	mem_check(ptr);
	check(idx < ptr->size && idx >= 0,"idx out of scope %d",idx);
	mem_check(ptr->buckets[idx]);
	ptr->buckets[idx] = NULL;
	return TRUE;
error:
	return ERROR;
}

int c00_array_list_remove_free(struct c00_array_list *ptr, int idx){
	mem_check(ptr);
	check(idx < ptr->size && idx >= 0,"idx out of scope %d",idx);
	mem_check(ptr->buckets[idx]);
	free(ptr->buckets[idx]);
	ptr->buckets[idx] = NULL;
	return TRUE;
error:
	return ERROR;
}
int c00_array_list_get(struct c00_array_list *ptr, int idx, void **val){
	mem_check(ptr);
	check(idx < ptr->size && idx >= 0,"idx out of scope %d",idx);
	mem_check(ptr->buckets[idx]);
	*val = ptr->buckets[idx];
	mem_check(val);
	return TRUE;
error:
	return ERROR;
}

#ifdef USEC00TESTS


int main(int argc, char *argv[]){
	HEAD_TEST("Array_LIST");
	struct c00_array_list *list;
	list = malloc(sizeof(struct c00_array_list));
	ASSERT_TEST("init",TRUE,c00_array_list_init(list,50));
	char *result;
	ASSERT_TEST("get empty",ERROR, c00_array_list_get(list,22,(void *)&result));
	char *insert = malloc(20 * sizeof(char));
	strcpy(insert,"hallo");
	ASSERT_TEST("insert",TRUE,c00_array_list_set(list,0,insert));

	ASSERT_TEST("get",TRUE,c00_array_list_get(list,0,(void *)&result));

	if(strcmp(result,"hallo") == 0){
		ASSERT_TEST("check_get_equal",TRUE,TRUE);
	}	
	
	ASSERT_TEST("remove_free",TRUE,c00_array_list_remove_free(list,0));

	insert = malloc(20 * sizeof(char));
	strcpy(insert,"hallo2");

	ASSERT_TEST("insert",TRUE,c00_array_list_set(list,0,insert));

	if(strcmp(result,"hallo2") == 0){
		ASSERT_TEST("check_get_equal",TRUE,TRUE);
	}	

	ASSERT_TEST("remove",TRUE,c00_array_list_remove(list,0));

	free(insert);


	ASSERT_TEST("destroy",TRUE,c00_array_list_destroy_free(list));

}
#endif
