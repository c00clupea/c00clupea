#include "util.h"


int print_log(FILE *fp, char *text){
	int res = 1;
	if(fp){
		fprintf(fp,text);
		res = 0;
	}
	return res;
	
}	

int print_safe_log(pthread_mutex_t *mtx, FILE *fp, char *txt){
	if(pthread_mutex_lock(mtx) != 0){
		syslog(LOG_ERR,"logwriter is not able to lock");
		return 1;
	}

	fprintf(fp,txt);
	if(pthread_mutex_unlock(mtx)!=0){
		syslog(LOG_ERR,"problem with unlock in consumer");
		return 1;
	}

}
