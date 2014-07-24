#include "util.h"


int print_log(FILE *fp, char *text){
	int res = 1;
	if(fp){
		fprintf(fp,text);
		res = 0;
	}
	return res;
	
}	

int init_safe_log(struct safe_log *logger, char *file_name){
	logger = malloc(sizeof(struct safe_log));
	logger->mtx = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(logger->mtx,NULL);
	logger->fp = fopen(file_name,"w");
}

int change_safe_log_file(struct safe_log *logger, char *filename){
	if(pthread_mutex_lock(logger->mtx) != 0){
		syslog(LOG_ERR,"logwriter is not able to lock");
		return 1;
	}

	fclose(logger->fp);
	logger->file_name = filename;

	logger->fp = fopen(filename,"w");

	if(pthread_mutex_unlock(logger->mtx)!=0){
		syslog(LOG_ERR,"problem with unlock in consumer");
		return 1;
	}
}

int close_safe_log(struct safe_log *logger){
	fclose(logger->fp);
	free(logger->file_name);
	free(logger->mtx);
	free(logger);
}

int print_safe_log(struct safe_log *logger, char *txt){
	if(pthread_mutex_lock(logger->mtx) != 0){
		syslog(LOG_ERR,"logwriter is not able to lock");
		return 1;
	}

	if(logger->fp){	
		fprintf(logger->fp,txt);
	}

	if(pthread_mutex_unlock(logger->mtx)!=0){
		syslog(LOG_ERR,"problem with unlock in consumer");
		return 1;
	}
	return 0;

}
