#include "strategy_http_path.h"

pthread_mutex_t mtx_http_path_write_lock = PTHREAD_MUTEX_INITIALIZER;

const int max_http_path_line_length = HTTP_PATH_LINE_LEN;


int strategy_http_path(struct consumer_command *tmp_cmd){
	if(receive_http_path(tmp_cmd) != 0){
		syslog(LOG_ERR,"Error in recv http");
		return 1;
	}
        if(send_http_path(tmp_cmd) != 0){
		syslog(LOG_ERR,"Error in sending some http");
		return 1;
	}
	return 0;
}
int receive_http_path(struct consumer_command *tmp_cmd){
	FILE *fr;
	fr = fdopen(dup(tmp_cmd->peer_socket),"r");
	char header_line[max_http_path_line_length];
	if(fr){
		increment_count(tmp_cmd);
	}


	return 0;
}
int send_http_path(struct consumer_command *tmp_cmd){
	return 0;
}
