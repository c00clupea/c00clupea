AM_CFLAGS =  -std=c99 -Wall -Wextra -pedantic -pthread -D_THREAD_SAFE

AM_CPPFLAGS = -DALLOWED_OPTS='"Vhp:b:c:s:"' -DINET_FAM=AF_INET -DMAINCONFIG='"$(sysconfdir)/c00clupea/c00clupea.config"' -DSTD_LOG_LEN=1024 -DSTD_FLUSH_COUNT=1 -DLOG_MAIN_TEMPLATE='"$(localstatedir)/log/c00clupea/c00clupea_%d.log"'




bin_PROGRAMS = c00clupea

c00clupea_SOURCES = 	global.h c00_convenience.h\
			cooclupea.c cooclupea.h\
			config.c config.h\
			ringbuffer.c ringbuffer.h\
			strategy.c strategy.h\
			strategies/strategy_dev_null.c strategies/strategy_dev_null.h\
			strategies/strategy_http_simple.c strategies/strategy_http_simple.h\
			strategies/strategy_http_path.c strategies/strategy_http_path.h\
			util/c00_hashmap.c util/c00_hashmap.h\
			strategies/http_codes.h\
			util.c util.h


