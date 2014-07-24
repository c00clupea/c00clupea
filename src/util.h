#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>
#include <pthread.h>
#include <syslog.h>

int print_log(FILE *fp, char *text);

int print_safe_log(pthread_mutex_t *mtx, FILE *fp, char *txt);


#endif
