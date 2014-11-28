/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 * 
 * File:	c00clupea_sim.h
 * created: 	Thu Sep 11 08:28:03 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */

#ifndef C00CLUPEA_SIM_H
#define C00CLUPEA_SIM_H
#include <stdio.h>
#include "global.h"



#ifdef C00SUNAME
#include "coreutils/c00s_uname.h"
#endif

#ifdef C00SWHOAMI
#include "coreutils/c00s_whoami.h"
#endif

#ifdef C00SUPTIME
#include "coreutils/c00s_uptime.h"
#endif

#ifdef C00SUSLEEP
#include "coreutils/c00s_usleep.h"
#endif

#ifdef C00SCAT
#include "coreutils/c00s_cat.h"
#endif

#ifdef C00STRUE
#include "coreutils/c00s_true.h"
#endif

#ifdef C00SFALSE
#include "coreutils/c00s_false.h"
#endif

#ifdef C00SYES
#include "coreutils/c00s_yes.h"
#endif

#endif
