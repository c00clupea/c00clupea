#ifndef STRATEGY_HTTP_PATH_H
#define STRATEGY_HTTP_PATH_H
#include "../strategy.h"


#define HTTP_PATH_HEADER_LINE 128
#define HTTP_PATH_LINE_LEN 8192

int strategy_http_path(struct consumer_command *tmp_cmd);
int receive_http_path(struct consumer_command *tmp_cmd);
int send_http_path(struct consumer_command *tmp_cmd);


#endif
