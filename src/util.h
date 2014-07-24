#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>
#include <pthread.h>
#include <syslog.h>
#include <stdlib.h>


#define LOG_LVL_DEBUG = 1
#define LOG_LVL_INFO = 2
#define LOG_LVL_WARN = 3
#define LOG_LVL_ERR = 4

struct safe_log{
	char *file_name;
	pthread_mutex_t *mtx;
	FILE *fp;
};


//int print_log(FILE *fp, char *text);

int init_safe_log(struct safe_log *logger, char *file_name);
int change_safe_log_file(struct safe_log *logger, char *filename);
int close_safe_log(struct safe_log *logger);
int print_safe_log(struct safe_log *logger, char *txt);


#endif
