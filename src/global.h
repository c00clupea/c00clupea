#ifndef GLOBAL_H
#define GLOBAL_H

#include "conf.h"

#include "util/util.h"
#include "c00_convenience.h"


#ifndef VERSION
#define VERSION -1
#endif

#ifndef STDERR
#define STDERR stderr
#endif

#ifndef STDLOG
#define STDLOG LOG_NOTICE
#endif

#ifndef SYSLOG
#define SYSLOG LOG_DAEMON
#endif

#define HONEYPOT_NAME "c00Clupea Honeypot"
#define AUTHOR "C.Pohl"

#ifndef ALLOWED_OPTS
#define ALLOWED_OPTS "Vhp:b:c:s:"
#endif

#ifndef STANDARD_PORT
#define STANDARD_PORT 8080
#endif

#ifndef INET_FAM
#define INET_FAM AF_INET
#endif

#ifndef TCP_BACKLOG
#define TCP_BACKLOG 128
#endif

#ifndef WORKER_POOL
#define WORKER_POOL 10
#endif

#ifndef MAINCONFIG
#define MAINCONFIG "~/.c00clupea.config"
#endif

#ifndef CONFIG_LEN
#define CONFIG_LEN 128
#endif

#ifndef MAX_SERVER
#define MAX_SERVER 32
#endif

#ifndef MAIN_BUFFER_LEN
#define MAIN_BUFFER_LEN 1024
#endif

#ifndef STRAT_LEN
#define STRAT_LEN 3
#endif

#ifndef STRAT_DEFAULT
#define STRAT_DEFAULT 0
#endif


#ifndef LOG_MAIN_TEMPLATE
#define LOG_MAIN_TEMPLATE "/var/log/c00clupea/c00clupea_%d.log"
#endif

#ifndef LOG_MAIN_PATH
#define LOG_MAIN_PATH "/var/log/c00clupea/%s"
#endif

#ifndef STORAGE_TEMPLATE
#define STORAGE_TEMPLATE "/var/%s/%d"
#endif


#define FALSE 0
#define ERROR -1
#define TRUE 1

#ifdef WRITEC00CRAP

#define C00DEBUG(fmt,...)\
	fprintf(stdout,"%s:%d ",__FILE__,__LINE__);\
	fprintf(stdout,fmt,__VA_ARGS__);\
	fprintf(stdout,"\n")

#define C00REACH(id)					\
	fprintf(stdout,"reach: %d --> %s:%d\n",id,__FILE__,__LINE__)

#else
#define C00DEBUG(fmt,...)
#define C00REACH(id)

#endif

#ifdef USEC00TESTS

#define HEAD_TEST(name)\
	fprintf(stdout,"######Start TEST %s######\n",name)

#define ASSERT_TEST(name,expect,result)		\
	if(result != expect){\
		fprintf(stdout,"TEST: %s failed\n",name);	\
		exit(1);						\
	}\
	else{\
		fprintf(stdout,"TEST: %s passed\n",name);	\
	}\

#define MSG_TEST(name)\
	fprintf(stdout,"TEST:%s \n",name)

#define RESULT_TEST(fmt,...)\
	fprintf(stdout,fmt,__VA_ARGS__)

#endif

//Some ideas from http://c.learncodethehardway.org/book/ex20.html
#define check(A, M, ...) if(!(A)) { C00DEBUG(M, __VA_ARGS__); syslog(LOG_ERR,M,__VA_ARGS__);goto error; }

#define mem_check(A) check((A), "%d Out of memory.",-1)


#endif
