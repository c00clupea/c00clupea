AM_CFLAGS =  -std=c99 -Wall -Wextra -pedantic -pthread -D_THREAD_SAFE

AM_CPPFLAGS =  -DSYSLOG=LOG_DAEMON -DALLOWED_OPTS='"Vhp:b:c:s:"' -DSTDERR=stderr -DSTDLOG=LOG_NOTICE -DINET_FAM=AF_INET -DTCP_BACKLOG=128 -DWORKER_POOL=10 -DMAIN_BUFFER_LEN=1024  -DMAINCONFIG='"$(sysconfdir)/c00clupea/c00clupea.config"' -DSTRAT_DEFAULT=0 -DSTD_LOG_LVL=2 -DSTD_LOG_LEN=1024 -DSTD_FLUSH_COUNT=1 -DLOG_MAIN_TEMPLATE='"$(localstatedir)/log/c00clupea/c00clupea_%d.log"'


bin_PROGRAMS = c00clupea

c00clupea_SOURCES = 	global.h\ c00_convenience.h\
			cooclupea.c cooclupea.h\
			config.c config.h\
			ringbuffer.c ringbuffer.h\
			strategy.c strategy.h\
			strategies/strategy_dev_null.c strategies/strategy_dev_null.h\
			strategies/strategy_http_simple.c strategies/strategy_http_simple.h\
			strategies/strategy_http_path.c strategies/strategy_http_path.h\
			util/c00_hashmap.c util/c00_hashmap.h\
			http_codes.h\
			util.c util.h


