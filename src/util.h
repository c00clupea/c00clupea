#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>
#include <pthread.h>
#include <syslog.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include "global.h"

#ifndef STD_LOG_LEN 
#define STD_LOG_LEN 1024
#endif


#ifndef STD_FLUSH_COUNT
#define STD_FLUSH_COUNT 0
#endif


#ifndef STD_LOG_LVL
#define STD_LOG_LVL 2
#endif


#define LOG_LVL_DEBUG 1
#define LOG_LVL_INFO 2
#define LOG_LVL_WARN 3
#define LOG_LVL_ERR 4

#define MAX_FR_TO_LOG_LEN 10485760


#define LOGGER(logger,loglvl,fmt,...)\
	print_safe_log(logger,loglvl,fmt,__VA_ARGS__)

#define LOGGER_DEBUG(logger,fmt,...)\
	c00_print_safe_log(logger,LOG_LVL_DEBUG,fmt,__VA_ARGS__)

#define LOGGER_INFO(logger,fmt,...)\
	c00_print_safe_log(logger,LOG_LVL_INFO,fmt,__VA_ARGS__)

#define LOGGER_WARN(logger,fmt,...)\
	c00_print_safe_log(logger,LOG_LVL_WARN,fmt,__VA_ARGS__)

#define LOGGER_ERROR(logger,fmt,...)\
	c00_print_safe_log(logger,LOG_LVL_ERR,fmt,__VA_ARGS__)

#define LOGGER_NLOG(logger,loglvl,fp,fmt,...)\
	c00_print_safe_single_log(logger,loglvl,fp,fmt,__VA_ARGS__)

#define LOGGER_NLOG_FR(logger,loglvl,fmt,fr,...)\
	c00_print_safe_single_log_fr(logger,loglvl,fmt,fr,__VA_ARGS__)

struct safe_log{
	char *file_name;
	pthread_mutex_t *mtx;
	FILE *fp;
	int log_level;
	int flush_count;
};


//int print_log(FILE *fp, char *text);

struct safe_log *c00_init_safe_log(char *file_name);
int c00_change_safe_log_file(struct safe_log *logger, char *filename);
int c00_close_safe_log(struct safe_log *logger);
int c00_print_safe_log(struct safe_log *logger,int log_level, char *txt,...);
int c00_print_safe_single_log_fr(struct safe_log *logger, int log_lvl, char *file, char *txt,FILE *fr,...);
int c00_print_safe_single_log(struct safe_log *logger, int log_lvl,char *file, char *txt,...);
int c00_create_unique_log_file(char *append,char *end, char *filename);
int c00_get_current_time(char *t, char *fmt,int len_buf);
int c00_get_hash_str(char *val,unsigned int len);
int c00_util_create_config_path(char *rel_file, char *full_file);
#endif
