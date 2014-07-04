#include <stdio.h>

struct test1{
	int a;
	int b;
}t11,t12,t13;

struct test2{
	int a;
	int b;
	int c;
}t21,t22;

int main(){
	struct test1* test[20];

	t11.a = 1;
	t11.b = 2;
	t12.a = 3;
	t12.b = 4;
	t21.a = 5;
	t21.b = 6;
	t21.c = 7;

	test[0] = &t11;
	test[1] = &t12;

	for(int i = 0;i<2;i++){
		printf("a %d b %d",test[i]->a,test[i]->b);
	}

	t11.a = 21;
	for(int i = 0;i<2;i++){
		printf("a %d b %d",test[i]->a,test[i]->b);
	}

	test[0]->a = 29;

	printf("a %d",t11.a);

}


