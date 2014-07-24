#ifndef STRATEG_HTTP_SIMPLE_H
#define STRATEG_HTTP_SIMPLE_H
#include "strategy.h"

int strategy_http_simple(struct consumer_command *tmp_cmd);

static int receive_simple_http(struct consumer_command *tmp_cmd);
static int send_simple_http(struct consumer_command *tmp_cmd);
#endif
