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
bin_PROGRAMS += c00clupea_honeymaster
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

connect_sources = util/c00_message.h util/c00_message.c

add_sources = global.h util/util.c util/util.h util/busybox_cccc.h util/getopt32.c util/c00s_xatonum.h util/c00s_xatonum.c util/bb_iobridge.c util/c00b_sysinfo.h util/c00b_sysinfo.c util/bb_util.c ${connect_sources}

c00clupeabox_SOURCES = c00clupea_sim.c c00clupea_sim.h ${add_sources}

c00clupea_honeymaster_SOURCES = global.h c00clupea_honeymaster.h c00clupea_honeymaster.c ${connect_sources} util/c00_iniparser.h util/c00_iniparser.c util/c00_dictionary.h util/c00_dictionary.c util/ringbuffer.c util/ringbuffer.h util/util.h util/util.c

if C00SWITHPREFIX
c00spref=c00nb-
else
c00spref=
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
__c00spref_uptime_SOURCES = ${add_sources} coreutils/c00s_uptime.c coreutils/c00s_uptime.h
endif
endif

if C00SUSLEEP
if C00SWITHLINK
c00clupeabox_SOURCES += coreutils/c00s_usleep.c coreutils/c00s_usleep.h
else
bin_PROGRAMS += ${c00spref}usleep
__c00spref_usleep_SOURCES = ${add_sources} coreutils/c00s_usleep.c coreutils/c00s_usleep.h
endif
endif

if C00SCAT
if C00SWITHLINK
c00clupeabox_SOURCES += coreutils/c00s_cat.c coreutils/c00s_cat.h
else
bin_PROGRAMS += ${c00spref}cat
__c00spref_cat_SOURCES = ${add_sources} coreutils/c00s_cat.c coreutils/c00s_cat.h
endif
endif


if C00STRUE
if C00SWITHLINK
c00clupeabox_SOURCES += coreutils/c00s_true.c coreutils/c00s_true.h
else
bin_PROGRAMS += ${c00spref}true
__c00spref_true_SOURCES = ${add_sources} coreutils/c00s_true.c coreutils/c00s_true.h
endif
endif

#be careful with the name but using FALSE is really mess cause makeconf does not like it so we use FalSE
if C00SFalSE
if C00SWITHLINK
c00clupeabox_SOURCES += coreutils/c00s_false.c coreutils/c00s_false.h
else
bin_PROGRAMS += ${c00spref}false
__c00spref_false_SOURCES = ${add_sources} coreutils/c00s_false.c coreutils/c00s_false.h
endif
endif

if C00SYES
if C00SWITHLINK
c00clupeabox_SOURCES += coreutils/c00s_yes.c coreutils/c00s_yes.h
else
bin_PROGRAMS += ${c00spref}yes
__c00spref_yes_SOURCES = ${add_sources} coreutils/c00s_yes.c coreutils/c00s_yes.h
endif
endif

if C00SSTRINGS
if C00SWITHLINK
c00clupeabox_SOURCES += coreutils/c00s_strings.c coreutils/c00s_strings.h
else
bin_PROGRAMS += ${c00spref}strings
__c00spref_strings_SOURCES = ${add_sources} coreutils/c00s_strings.c coreutils/c00s_strings.h
endif
endif
