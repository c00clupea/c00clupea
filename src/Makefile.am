AM_CFLAGS =  -std=gnu99 -Wall -Wextra -pedantic -D_THREAD_SAFE

if NEEDPTHREAD
AM_CFLAGS += -pthread
endif

if CLANG
AM_CFLAGS += -Wno-extended-offsetof
endif

AM_CPPFLAGS = 

bin_PROGRAMS =

if C00CLUPEA
bin_PROGRAMS += c00clupea
endif

if C00CLUPEABOX
if C00SWITHLINK
bin_PROGRAMS += c00clupeabox
endif
endif

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

c00clupeabox_SOURCES = c00clupea_sim.c c00clupea_sim.h\
                       global.h\
                       util/util.c util/util.h\
                       util/busybox_cccc.h\
                       util/getopt32.c\
                       util/c00b_sysinfo.h util/c00b_sysinfo.c

if C00SWITHPREFIX
c00spref=c00nb-
else
c00spref=
endif

if !C00SWITHLINK
add_sources = global.h util/util.c util/util.h util/busybox_cccc.h util/getopt32.c
endif

if C00SUNAME
if C00SWITHLINK
c00clupeabox_SOURCES += coreutils/c00s_uname.c coreutils/c00s_uname.h
else
bin_PROGRAMS += ${c00spref}uname
__c00spref_uname_SOURCES = ${add_sources} coreutils/c00s_uname.c coreutils/c00s_uname.h
endif
endif

if C00SWHOAMI
if C00SWITHLINK
c00clupeabox_SOURCES += coreutils/c00s_whoami.c coreutils/c00s_whoami.h
else
bin_PROGRAMS += ${c00spref}whoami
__c00spref_whoami_SOURCES = ${add_sources} coreutils/c00s_whoami.c coreutils/c00s_whoami.h
endif
endif

if C00SUPTIME
if C00SWITHLINK
c00clupeabox_SOURCES += coreutils/c00s_uptime.c coreutils/c00s_uptime.h
else
bin_PROGRAMS += ${c00spref}uptime
__c00spref_uptime_SOURCES = ${add_sources} util/c00b_sysinfo.h util/c00b_sysinfo.c coreutils/c00s_uptime.c coreutils/c00s_uptime.h
endif
endif
