#ifndef GLOBAL_H
#define GLOBAL_H

#include "conf.h"

/*#include "util/util.h"*/
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

#define C00RKILL()\
	fprintf(stdout,"reached kill code");exit(1)

#define C00FKILL(fmt,...)\
	fprintf(stdout,"%s:%d ",__FILE__,__LINE__);\
	fprintf(stdout,fmt,__VA_ARGS__);\
	fprintf(stdout,"\n");\
	exit(1)


#else
#define C00DEBUG(fmt,...)
#define C00REACH(id)
#define C00RKILL()
#define C00FKILL(fmt,...)

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

#define C00SYSDEBUG(fmt,...)\
	syslog(LOG_DEBUG,fmt,__VA_ARGS__)

#define C00SYSINFO(fmt,...)\
	syslog(LOG_INFO,fmt,__VA_ARGS__)

#define C00SYSERROR(fmt,...)\
	syslog(LOG_ERR,fmt,__VA_ARGS__)

#define C00SYSALERT(fmt,...)\
	syslog(LOG_ALERT,fmt,__VA_ARGS__)

#define C00SYSDEBUGN(fmt)\
	syslog(LOG_DEBUG,fmt,)

#define C00SYSINFON(fmt)\
	syslog(LOG_INFO,fmt)

#define C00SYSERRORN(fmt)\
	syslog(LOG_ERR,fmt)

#define C00SYSALERTN(fmt)\
	syslog(LOG_ALERT,fmt)

#define C00STDOUTN(fmt)\
	printf(fmt)

#define C00STDOUTEXITN(fmt,code)			\
	printf(fmt);exit(code)

#define C00STDOUT(fmt,...)				\
	printf(fmt,__VA_ARGS__)

#define C00STDOUTEXIT(fmt,code,...)		\
	printf(fmt,__VA_ARGS__);exit(code)



#define FLP __FILE__,__LINE__

#define UNUSED __attribute__((unused))

#define DEVELOP

#ifdef DEVELOP
#define D_LN "c00_"
#else
#define D_LN
#endif


#ifndef FSHIFT
# define FSHIFT 16              /* nr of bits of precision */
#endif
#define FIXED_1      (1 << FSHIFT)     /* 1.0 as fixed-point */
#define LOAD_INT(x)  (unsigned)((x) >> FSHIFT)
#define LOAD_FRAC(x) LOAD_INT(((x) & (FIXED_1 - 1)) * 100)


#define check_box(N,V)				\
	C00DEBUG("check %s",V);			\
	if(strcmp(argv[0],V) == 0){		\
C00DEBUG("found %s",V);\
	return N##_main(argc,argv);		\
	}\



#define check_argv(M,N,O)		\
	(strcmp(argv[M],N) == 0) || (strcmp(argv[M],O) == 0)	\




//Some ideas from http://c.learncodethehardway.org/book/ex20.html
#define check(A, M, ...) if(!(A)) { C00DEBUG(M, __VA_ARGS__); syslog(LOG_ERR,M,__VA_ARGS__);goto error; }

#define echocheck(A,M,...)if(!(A)) { C00DEBUG(M, __VA_ARGS__); fprintf(stderr,M,__VA_ARGS__);goto error; }

#define echoerror(M,...) C00DEBUG(M, __VA_ARGS__); fprintf(stderr,M,__VA_ARGS__);goto error;

#define mem_check(A) check((A), "%d Out of memory.",-1)


//end ideas

#define check_idx(I,L)\
	check(0 <= I && I < L && L != 0,"idx %d out of bound %s %d",I,FLP)

#endif
