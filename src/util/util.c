#include "util.h"

static int 	_c00_seek_file(FILE *fp,int offset);
static void 	_c00_flush_log(struct c00_safe_log *logger);

int c00_util_file_size(const char *fpath){
	if(c00_util_file_exist(fpath) == FALSE){
		return -1;
	}	
	struct stat st_f;
	stat(fpath,&st_f);
	return st_f.st_size;
}

int c00_util_file_exist(const char *fpath){
	FILE *fp;
	fp = fopen(fpath,"r");
	if(fp){
		fclose(fp);
		return TRUE;
	}
	return FALSE;
	
}

int _c00_seek_file(FILE *fp,int offset){
	if(fseek(fp,offset,SEEK_SET) == -1){
		return 1;
	}
	return 0;
}
	
struct c00_safe_log *c00_init_safe_log( char *file_name){
	struct c00_safe_log *logger = malloc(sizeof(struct c00_safe_log));
	logger->mtx = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(logger->mtx,NULL);
	logger->fp = fopen(file_name,"a");
	logger->flush_count = 0;
	if(!logger->fp){
		syslog(LOG_ERR,"Sorry but %s is not writable or permission problem or sth else",file_name);
		exit(1);
	}
	return logger;
}

int c00_change_safe_log_file(struct c00_safe_log *logger, char *filename){
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



int c00_close_safe_log(struct c00_safe_log *logger){
	fclose(logger->fp);
	free(logger->file_name);
	free(logger->mtx);
	free(logger);
	return 0;
}

void _c00_flush_log(struct c00_safe_log *logger){
	logger->flush_count++;
	if(logger->flush_count >= STD_FLUSH_COUNT){
		fflush(logger->fp);
		logger->flush_count = 0;
	}
}


int c00_get_current_time(char *t_buf, char *fmt,int len_buf){
	time_t now = 0;
	struct tm *t;
       	now = time(NULL);
       	t = gmtime(&now);

       	strftime(t_buf,len_buf - 1 ,fmt,t);
	return 0;
}


int c00_print_safe_single_log_fr(char *file, char *txt, FILE *fr,...){
	FILE *fp;
	fp = fopen(file,"w");
	int chr;

	if(fp){

		char t_buf[31];

		c00_get_current_time(t_buf,"[%Y.%m.%d %T]",31);
	        
		fprintf(fp,"[%s]",t_buf);

		va_list args;
		va_start(args,fr);
		fprintf(fp,txt,args);
		va_end(args);
		fprintf(fp,"\n[PAYLOAD]\n");

		if(_c00_seek_file(fr,0) != 0){
			syslog(LOG_ERR,"CRitical, can not set lseek in fr");
			fclose(fp);
			return 1;
		}

		unsigned long count_len = 0;
		while((chr = getc(fr)) != EOF || count_len > MAX_FR_TO_LOG_LEN){
			fprintf(fp,"%c",chr);
			count_len ++;
		}

		if(_c00_seek_file(fr,0) != 0){
			syslog(LOG_ERR,"CRitical, can not set lseek in fr");
			fclose(fp);
			return 1;
		}

		fclose(fp);
	}
	else{
		syslog(LOG_ERR,"not able to open %s to write",file);
		return 1;
	}

	return 0;
}

int c00_get_hash_str(char *val,unsigned int len){
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

int c00_get_hash_int(int val){
	return val;	
}

int c00_create_unique_log_file(char *append,char *end, char *filename){
	
	char time[31];
	int hash = 0;
	char to_hash[PATH_MAX];
	char simple_file[PATH_MAX];

	c00_get_current_time(time,"[%Y.%m.%d %T]",31);

	snprintf(to_hash,PATH_MAX,"%s_%s.%s",time,append,end);

	hash = c00_get_hash_str(to_hash,PATH_MAX);

	snprintf(simple_file,PATH_MAX,"%s_%d_%s.%s",time,hash,append,end);
	
	snprintf(filename,PATH_MAX,LOG_MAIN_PATH,simple_file);

	return 0;
}

int c00_print_safe_log(struct c00_safe_log *logger, int log_level, char *txt,...){
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
     			_c00_flush_log(logger);

		}

		if(pthread_mutex_unlock(logger->mtx)!=0){
			syslog(LOG_ERR,"problem with unlock in consumer");
			return 1;
		}
	}
	return 0;

}


int c00_util_create_config_path(char *full_file, char *rel_file){
	char path[PATH_MAX];

	snprintf(path,PATH_MAX,"%s/%s",STRAT_CONFIG_PATH,rel_file);

	strncpy(full_file,path,PATH_MAX);
	C00DEBUG("create file path %s",full_file);
	
	return TRUE;
}
