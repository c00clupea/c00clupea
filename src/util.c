#include "util.h"


int print_log(FILE *fp, char *text){
	int res = 1;
	if(fp){
		fprintf(fp,text);
		res = 0;
	}
	return res;
	
}	
