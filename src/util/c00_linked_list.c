#include "c00_linked_list.h"




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
int c00_linked_list_destroy(struct c00_linked_list *ptr){
	return ERROR;
}
int c00_linked_list_destroy_free(struct c00_linked_list *ptr){
	return ERROR;
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
int c00_linked_list_imove(struct c00_linked_list *ptr, signed int range){
	return ERROR;
}
/**i... means index on the current index (move with imove) this action will be done**/
int c00_linked_list_iget(struct c00_linked_list *ptr, void **val){
	check(ptr->size > 0,"linked list empty %s %d",FLP);
	check_idx(ptr->idx,ptr->size);
	
error:	
	return ERROR;
}

int	_c00_set_bucket(struct c00_linked_list *ptr, struct c00_linked_list_bucket *ptr_buc){
	if(ptr->size == 0){
		ptr->first = ptr_buc;
		ptr->last = ptr_buc;
		ptr->actual = ptr_buc;
		ptr->idx = 0;
		ptr->size ++;
		return TRUE;
	}
	check(1==0,"not working %s %d",FLP);
	struct c00_linked_list_bucket *old_act;
	old_act = ptr->actual;
	struct c00_linked_list_bucket *old_right;
	old_right = old_act->right;
	old_act->right = ptr_buc;
	ptr_buc->right = old_right;// (NULL or real)
	ptr_buc->left = old_act;
	if(old_right != NULL){
		old_right->left = ptr_buc;
	}
	ptr->size ++;
	return TRUE;
error:
	return ERROR;
	
}

int c00_linked_list_iset(struct c00_linked_list *ptr, void *val){

	struct c00_linked_list_bucket *tmp_buc = malloc(sizeof(struct c00_linked_list_bucket);
       
	tmp_buc->val = val;
	tmp_buc->left = NULL;
  	tmp_buc->right = NULL;

	return ERROR;
}
int c00_linked_list_iremove(struct c00_linked_list *ptr){
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
	ASSERT_TEST("destroy",TRUE,c00_linked_list_destroy_free(list));
}
#endif
