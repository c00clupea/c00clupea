#ifndef STRATEGY_H
#define STRATEGY_H
#include <syslog.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "cooclupea.h"

/**Strategies**/

#include "strategies/strategy_dev_null.h"
#include "strategies/strategy_http_simple.h"
#include "strategies/strategy_http_path.h"

int c00_strategy_init();
int(*c00_strategy_get_by_idx(int idx))(struct c00_consumer_command *);

#endif
