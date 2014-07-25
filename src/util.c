#include "util.h"


int print_log(FILE *fp, char *text){
	int res = 1;
	if(fp){
		fprintf(fp,text);
		res = 0;
	}
	return res;
	
}	

struct safe_log *init_safe_log( char *file_name){
	struct safe_log *logger = malloc(sizeof(struct safe_log));
	logger->mtx = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(logger->mtx,NULL);
	logger->fp = fopen(file_name,"w");
	logger->flush_count = 0;
	return logger;
}

int change_safe_log_file(struct safe_log *logger, char *filename){
	if(pthread_mutex_lock(logger->mtx) != 0){
		syslog(LOG_ERR,"logwriter is not able to lock");
		return 1;
	}

	fclose(logger->fp);
	logger->file_name = filename;

	logger->fp = fopen(filename,"a");

	if(pthread_mutex_unlock(logger->mtx)!=0){
		syslog(LOG_ERR,"problem with unlock in consumer");
		return 1;
	}
	return 0;
}

int close_safe_log(struct safe_log *logger){
	fclose(logger->fp);
	free(logger->file_name);
	free(logger->mtx);
	free(logger);
	return 0;
}

void flush_log(struct safe_log *logger){
	logger->flush_count++;
	if(logger->flush_count > STD_FLUSH_COUNT){
		fflush(logger->fp);
	}
	logger->flush_count = 0;
}

int print_safe_log(struct safe_log *logger, int log_level, char *txt,...){
	if(log_level >= logger->log_level){

		if(pthread_mutex_lock(logger->mtx) != 0){
			syslog(LOG_ERR,"logwriter is not able to lock");
			return 1;
		}

		if(logger->fp){	
			time_t now = 0;
			struct tm *t;
			now = time(NULL);
			t = gmtime(&now);
			char tbuf[31];
			strftime(tbuf,30,"[%Y.%m.%d %T]",t);
			va_list args;
			va_start(args,txt);
			char the_log[STD_LOG_LEN];
			vsnprintf(the_log,STD_LOG_LEN,txt,args);
			fprintf(logger->fp,"%s %s\n",tbuf,the_log);
			va_end(args);

     			flush_log(logger);

		}

		if(pthread_mutex_unlock(logger->mtx)!=0){
			syslog(LOG_ERR,"problem with unlock in consumer");
			return 1;
		}
	}
	return 0;

}
