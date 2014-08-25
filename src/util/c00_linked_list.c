#include "c00_linked_list.h"

/**mode 0 = actual idx, mode 1 begin, mode 2 end**/
static inline int _c00_set_bucket(struct c00_linked_list *ptr, struct c00_linked_list_bucket *ptr_buc);
static inline int _c00_move_to_start(struct c00_linked_list *ptr);


int c00_linked_list_init(struct c00_linked_list *ptr){
	mem_check(ptr);
	ptr->first = NULL;
	ptr->last = NULL;
	ptr->actual = NULL;
	ptr->idx = 0;
	ptr->size = 0;
	return TRUE;

error:
	return ERROR;
}

static inline int _c00_move_to_start(struct c00_linked_list *ptr){
	if(ptr->size > 0){
		ptr->idx = 0;
		ptr->actual = ptr->first;
	}
	return TRUE;
}
int c00_linked_list_destroy(struct c00_linked_list *ptr){
	_c00_move_to_start(ptr);
	
	while(ptr->size != 0){
		void *val;
		c00_linked_list_iremove(ptr,&val);
       	}
	free(ptr);
	return TRUE;
}
int c00_linked_list_destroy_free(struct c00_linked_list *ptr){
	_c00_move_to_start(ptr);
	
	while(ptr->size != 0){
		void *val;
		c00_linked_list_iremove(ptr,&val);
		free(val);
       	}
	free(ptr);
	return TRUE;
}
int c00_linked_list_push_end(struct c00_linked_list *ptr, void *val){
	return ERROR;
}
int c00_linked_list_push_start(struct c00_linked_list *ptr, void *val){
	return ERROR;
}
int c00_linked_list_pop_end(struct c00_linked_list *ptr, void **val){
	return ERROR;
}
int c00_linked_list_pop_start(struct c00_linked_list *ptr, void **val){
	return ERROR;
}
int c00_linked_list_set(struct c00_linked_list *ptr,int idx, void *val){
	return ERROR;
}
int c00_linked_list_get(struct c00_linked_list *ptr,int idx, void **val){
	return ERROR;
}
int c00_linked_list_remove(struct c00_linked_list *ptr, int idx){
	return ERROR;
}
int c00_linked_list_imove(struct c00_linked_list *ptr, int range){
	C00DEBUG("act size %d",ptr->size);
	check_idx(ptr->idx + range,ptr->size);
	
	for(int i = 0; i < abs(range); i++){
		if(range < 0){
			ptr->actual = ptr->actual->left;
		}
		else{
			ptr->actual = ptr->actual->right;
		}
	}
	ptr->idx = ptr->idx + range;
	
	return TRUE;
error:
	return ERROR;
}
/**i... means index on the current index (move with imove) this action will be done**/
int c00_linked_list_iget(struct c00_linked_list *ptr, void **val){
	check(ptr->size > 0,"linked list empty %s %d",FLP);
	check_idx(ptr->idx,ptr->size);
	*val = ptr->actual->val;
error:	
	return ERROR;
}

int _c00_set_bucket(struct c00_linked_list *ptr, struct c00_linked_list_bucket *ptr_buc){
	if(ptr->size == 0){
		ptr->first = ptr_buc;
		ptr->last = ptr_buc;
		ptr->actual = ptr_buc;
		ptr->idx = 0;
		ptr->size ++;
		return TRUE;
	}
	struct c00_linked_list_bucket *old_act;
	old_act = ptr->actual;
	struct c00_linked_list_bucket *old_left;
	old_left = old_act->left;
	if(old_left != NULL){
		old_left->right = ptr_buc;
		
	}else{
		ptr->first = ptr_buc;
	}
	ptr_buc->left = old_left;
	ptr_buc->right = old_act;
	old_act->left = ptr_buc;
	ptr->actual = ptr_buc;
	ptr->size ++;
	return TRUE;
error:
	return ERROR;
	
}

int c00_linked_list_iset(struct c00_linked_list *ptr, void *val){

	struct c00_linked_list_bucket *tmp_buc = malloc(sizeof(struct c00_linked_list_bucket));
	tmp_buc->val = val;
	tmp_buc->left = NULL;
  	tmp_buc->right = NULL;
	if(_c00_set_bucket(ptr,tmp_buc) == TRUE){
     		return TRUE;
      	}
	return ERROR;
}
int c00_linked_list_iremove(struct c00_linked_list *ptr, void **val){
	check(ptr->size > 0,"size is %d",ptr->size);	
	C00DEBUG("remove idx %d",ptr->idx);
	struct c00_linked_list_bucket *tmp_buc;
	tmp_buc = ptr->actual;
	ptr->size --;
	if(ptr->actual->left != NULL){
		ptr->actual->left->right = ptr->actual->right; //NULL or bucket
	}
	if(ptr->actual->right != NULL){
		ptr->actual->right->left = ptr->actual->left; // NULL or bucket
		ptr->actual = ptr->actual->right;
	}
	else{
		//actual idx moves left or is empty
		if(ptr->size > 0){
			ptr->actual = tmp_buc->left;
			ptr->idx --;
		}else{
			ptr->actual = NULL;
			ptr->first = NULL;
			ptr->last = NULL;
		}
	}
	
	if(ptr->actual && ptr->actual->right == NULL){
		ptr->last = ptr->actual;
	}
	if(ptr->actual && ptr->actual->left == NULL){
		ptr->first = ptr->actual;
	}
	val = tmp_buc->val;
	free(tmp_buc);
	
	return TRUE;
error:
	return ERROR;
}

#ifdef USEC00TESTS
int main(int argc, char *argv[]){
	HEAD_TEST("Linked List");
	struct c00_linked_list *list;
	list = malloc(sizeof(struct c00_linked_list));

	ASSERT_TEST("init", TRUE,c00_linked_list_init(list));
	char *result;
	ASSERT_TEST("empty get",ERROR,c00_linked_list_iget(list,(void *)&result));

	char *insert1 = malloc(20 * sizeof(char));
	strcpy(insert1,"hallo1");
	ASSERT_TEST("insert1",TRUE,c00_linked_list_iset(list,insert1));


	char *insert2 = malloc(20 * sizeof(char));
	strcpy(insert2,"hallo2");
	ASSERT_TEST("insert2",TRUE,c00_linked_list_iset(list,insert2));
	char *result1;

	c00_linked_list_iget(list,(void *)&result1);
	C00DEBUG("result: %s",result1);
	if(strcmp(result1,"hallo2") == 0){
		ASSERT_TEST("test get1",TRUE,TRUE);
	}else{
		ASSERT_TEST("test get1",FALSE,TRUE);
	}

	C00DEBUG("act res %s",list->actual->val);
	C00DEBUG("act +1 res %s",list->actual->right->val);
	ASSERT_TEST("move +1",TRUE,c00_linked_list_imove(list,1));
	ASSERT_TEST("move +1",1,list->idx);
	char *result2;
	c00_linked_list_iget(list,(void *)&result2);
	C00DEBUG("result2: %s",result2);
	if(strcmp(result2,"hallo1") == 0){
		ASSERT_TEST("test get2",TRUE,TRUE);
	}else{
		ASSERT_TEST("test get 2",FALSE,TRUE);
	}
	ASSERT_TEST("move -1",TRUE,c00_linked_list_imove(list,-1));
	ASSERT_TEST("move",0,list->idx);
	char *result3;

	c00_linked_list_iget(list,(void *)&result3);
	C00DEBUG("result3: %s",result3);
	if(strcmp(result3,"hallo2") == 0){
		ASSERT_TEST("test get3",TRUE,TRUE);
	}else{
		ASSERT_TEST("test get 3",FALSE,TRUE);
	}
	char *result4;

//	ASSERT_TEST("remove one",TRUE,c00_linked_list_iremove(list,(void *)&result4));

	char *result5;
//
//	ASSERT_TEST("remove one",TRUE,c00_linked_list_iremove(list,(void *)&result5));

	ASSERT_TEST("size",2,list->size);
//	ASSERT_TEST("idx",1,list->idx);
	ASSERT_TEST("destroy",TRUE,c00_linked_list_destroy_free(list));
}
#endif
