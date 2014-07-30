#ifndef STRATEGY_HTTP_PATH_H
#define STRATEGY_HTTP_PATH_H
#include "../strategy.h"
#include <limits.h>
#include "http_codes.h"

#define HTTP_PATH_HEADER_LINE 128
#define HTTP_PATH_LINE_LEN 8192
#define HTTP_PATH_LEN 1024
#define HTTP_PATH_METHOD_LEN 10


struct http_path_request{
	char 	http_path	[PATH_MAX];
	char 	http_method	[HTTP_PATH_METHOD_LEN];
	int 	minor_version;
	int 	major_version;
	int	http_response;      
};


int strategy_http_path(struct consumer_command *tmp_cmd);


#endif
