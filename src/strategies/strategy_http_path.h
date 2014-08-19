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

#define HTTP_PATH_STRATEGY_PLAIN 0
#define HTTP_PATH_STRATEGY_OK 1
#define HTTP_PATH_STRATEGY_FILE 2

#define HTTP_PATH_MIME_LEN 30



struct http_path_request{
	char 	http_path	[PATH_MAX];
	char 	http_method	[HTTP_PATH_METHOD_LEN];
	int 	minor_version;
	int 	major_version;
	int	http_response;      
};

//strategy 0 == plain file will be called with header
//strategy 1 == standard 200 header with file
//strategy 2 == header from similar file *.header
//strategy 200 -900 == standard header with error code

struct c00_http_path_single_path{
	char	path		[PATH_MAX];
	int	header_strategy;
	char	mime		[HTTP_PATH_MIME_LEN];
};

struct c00_http_path_globals{
	struct 	c00_hashmap 	*path_whitelist;
	char			htdocs_root[PATH_MAX];
};


int c00_strategy_http_path(struct c00_consumer_command *tmp_cmd);
int c00_strategy_http_path_init();

struct c00_http_path_globals *c00_http_path_glob;


#endif
