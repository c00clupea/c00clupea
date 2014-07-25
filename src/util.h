#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>
#include <pthread.h>
#include <syslog.h>
#include <stdlib.h>
#include <stdarg.h>

#ifndef STD_LOG_LEN 
#define STD_LOG_LEN 1024
#endif


#ifndef STD_FLUSH_COUNT
#define STD_FLUSH_COUNT 1
#endif


#ifndef STD_LOG_LVL
#define STD_LOG_LVL 2
#endif


#define LOG_LVL_DEBUG 1
#define LOG_LVL_INFO 2
#define LOG_LVL_WARN 3
#define LOG_LVL_ERR 4

#define LOGGER(logger,loglvl,fmt,...)\
	print_safe_log(logger,loglvl,fmt,__VA_ARGS__)

#define LOGGER_DEBUG(logger,fmt,...)\
	print_safe_log(logger,LOG_LVL_DEBUG,fmt,__VA_ARGS__)

#define LOGGER_INFO(logger,fmt,...)\
	print_safe_log(logger,LOG_LVL_INFO,fmt,__VA_ARGS__)

#define LOGGER_WARN(logger,fmt,...)\
	print_safe_log(logger,LOG_LVL_WARN,fmt,__VA_ARGS__)

#define LOGGER_ERROR(logger,fmt,...)\
	print_safe_log(logger,LOG_LVL_ERR,fmt,__VA_ARGS__)


struct safe_log{
	char *file_name;
	pthread_mutex_t *mtx;
	FILE *fp;
	int log_level;
	int flush_count;
};


//int print_log(FILE *fp, char *text);

struct safe_log *init_safe_log(char *file_name);
int change_safe_log_file(struct safe_log *logger, char *filename);
int close_safe_log(struct safe_log *logger);
int print_safe_log(struct safe_log *logger,int log_level, char *txt,...);


#endif
