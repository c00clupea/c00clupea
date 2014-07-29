#ifndef STRATEG_HTTP_SIMPLE_H
#define STRATEG_HTTP_SIMPLE_H
#include "../strategy.h"

#define HTTP_SIMPLE_HEADER_LINE 128
#define HTTP_SIMPLE_LINE_LEN 8192


int strategy_http_simple(struct consumer_command *tmp_cmd);

int receive_simple_http(struct consumer_command *tmp_cmd);
int send_simple_http(struct consumer_command *tmp_cmd);
#endif
