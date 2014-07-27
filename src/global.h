#ifndef GLOBAL_H
#define GLOBAL_H

#include "util.h"

#ifndef STDERR
#define STDERR stderr
#endif

#ifndef STDLOG
#define STDLOG LOG_NOTICE
#endif

#ifndef SYSLOG
#define SYSLOG LOG_DAEMON
#endif

#define VERSION "1.0"
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
#define MAINCONFIG "~/.pandora.config"
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
#define STRAT_LEN 2
#endif

#ifndef STRAT_DEFAULT
#define STRAT_DEFAULT 0
#endif




#endif
