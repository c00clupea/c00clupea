#ifndef STRATEGY_HTTP_PATH_H
#define STRATEGY_HTTP_PATH_H
#include "../strategy.h"
#include <limits.h>
#include "http_codes.h"
#include "../util/c00_hashmap.h"

#define HTTP_PATH_HEADER_LINE 128
#define HTTP_PATH_LINE_LEN 8192
#define HTTP_PATH_LEN 1024
#define HTTP_PATH_METHOD_LEN 10
#define HTTP_PATH_MAX_PATH 128


struct http_path_request{
	char 	http_path	[PATH_MAX];
	char 	http_method	[HTTP_PATH_METHOD_LEN];
	int 	minor_version;
	int 	major_version;
	int	http_response;      
};

struct c00_http_path_globals{
	struct 	c00_hashmap 	*path_whitelist;
	char			htdocs_root[PATH_MAX];
};


int strategy_http_path(struct consumer_command *tmp_cmd);
int c00_strategy_http_path_init();

struct c00_http_path_globals *c00_http_path_glob;


#endif
