AM_CFLAGS =  -std=gnu99 -Wall -Wextra -pedantic -pthread -D_THREAD_SAFE -Wno-extended-offsetof

AM_CPPFLAGS = 

bin_PROGRAMS = c00clupea c00clupea_sim

##never ever use tabs here...the += commands would not work

c00clupea_SOURCES = global.h\
                    c00_convenience.h\
		    cooclupea.c cooclupea.h\
		    strategy.c strategy.h\
		    util/config.c util/config.h\
		    util/ringbuffer.c util/ringbuffer.h\
		    util/util.c util/util.h\
		    util/c00_hashmap.c util/c00_hashmap.h\
		    util/c00_array_list.c util/c00_array_list.h\
		    util/c00_linked_list.c util/c00_linked_list.h\
		    strategies/strategy_dev_null.c strategies/strategy_dev_null.h\
		    strategies/strategy_http_simple.c strategies/strategy_http_simple.h\
		    strategies/strategy_http_path.c strategies/strategy_http_path.h\
		    strategies/http_codes.h

c00clupea_sim_SOURCES = c00clupea_sim.c c00clupea_sim.h\
                        global.h\
                        util/util.c util/util.h\
                        util/getopt32.c

if C00SUNAME
c00clupea_sim_SOURCES += coreutils/c00s_uname.c coreutils/c00s_uname.h
endif
