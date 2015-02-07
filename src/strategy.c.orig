/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 * 
 * File:	strategy.c
 * created: 	Wed Sep 10 23:18:37 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */

#include "strategy.h"

static int 		(*strategy_ptr[STRAT_LEN])(struct c00_consumer_command *) 	= {NULL};

int(*c00_strategy_get_by_idx(int idx))(struct c00_consumer_command *){
	if(idx < 0 && idx > (STRAT_LEN -1)){
    		syslog(LOG_ERR,"You tried strategy %d which is out of bound",idx);
    		return strategy_ptr[STRAT_DEFAULT];
  	}
  	return strategy_ptr[idx];
}


int c00_strategy_init()
{
        strategy_ptr[0] = &c00_strategy_dev_null;
	strategy_ptr[1] = &c00_strategy_http_simple;
	strategy_ptr[2] = &c00_strategy_http_path;
	c00_strategy_http_path_init();
	return 0;
}
