#include "strategy_http_path.h"

int destroy_http_path_request(struct http_path_request *pth_req);
int receive_http_path(struct consumer_command *tmp_cmd,struct http_path_request *pth_req);
int send_http_path(struct consumer_command *tmp_cmd);

int _c00_http_path_read_config(struct c00_hashmap *map);

pthread_mutex_t mtx_http_path_write_lock = PTHREAD_MUTEX_INITIALIZER;

const int max_http_path_line_len = HTTP_PATH_LINE_LEN;

const int max_http_path_header_len = HTTP_PATH_HEADER_LINE;

int strategy_http_path(struct consumer_command *tmp_cmd){
	
	struct http_path_request *pth_req;

	pth_req = malloc(sizeof(struct http_path_request));

	if(receive_http_path(tmp_cmd,pth_req) != 0){
		syslog(LOG_ERR,"Error in recv http");
		destroy_http_path_request(pth_req);
		return 1;
	}
        if(send_http_path(tmp_cmd) != 0){
		syslog(LOG_ERR,"Error in sending some http");
		destroy_http_path_request(pth_req);
		return 1;
	}
     	destroy_http_path_request(pth_req);
	return 0;
}

int _c00_http_path_read_config(struct c00_hashmap *map){
	FILE *fp;

	char path[PATH_MAX];
	snprintf(path,PATH_MAX,"%s/http_path_whitelist.config",STRAT_CONFIG_PATH);
	fp = fopen(path,"r");
	if(!fp){
		syslog(LOG_ERR,"Unable to open %s",path);
		return FALSE;
	}
	char line[HTTP_PATH_LINE_LEN + PATH_MAX + 200];
	char http_path[HTTP_PATH_LINE_LEN]; //will be copied
	while(fgets(line,sizeof(line),fp) != NULL){
		char *target_path = malloc(PATH_MAX * sizeof(char));
		if(sscanf(line,"%s %s",http_path,target_path) != 2){
			syslog(LOG_ERR,"[%s] not valid",line);
			C00DEBUG("[%s] is problematic",line);
		}
		else{
			c00_hashmap_add_key_value(map,http_path,sizeof(http_path),target_path);
			C00DEBUG("add %s --> %s",http_path,target_path);
		}
			
	}
	fclose(fp);
	return TRUE;
}

int c00_strategy_http_path_init(){
	c00_http_path_glob = malloc(sizeof(struct c00_http_path_globals));
	struct c00_hashmap *map;
	map = malloc(sizeof(struct c00_hashmap));
	c00_hashmap_init(map,HTTP_PATH_MAX_PATH,0);

	c00_http_path_glob->path_whitelist = map;
	_c00_http_path_read_config(map);	
	return TRUE;
}

int destroy_http_path_request(struct http_path_request *pth_req){
	free(pth_req);
	return 0;
}

int receive_http_path(struct consumer_command *tmp_cmd, struct http_path_request *pth_req){
	FILE *fr;
	fr = fdopen(dup(tmp_cmd->peer_socket),"r");
	char header_line[max_http_path_line_len];
	if(fr){
		
		increment_count(tmp_cmd);
		int count_lines = 0;
		char buffer[INET_ADDRSTRLEN];

		const char* result=inet_ntop(AF_INET,&(tmp_cmd->client.sin_addr),buffer,sizeof(buffer));
		char log_all[STD_LOG_LEN];
		snprintf(log_all,STD_LOG_LEN,"rcv from %s count %llu:\n",result,tmp_cmd->serverConfig->count->count);
		/**read the first line**/
		fgets(header_line,max_http_path_line_len,fr);

		if(sscanf(header_line,"%s %s HTTP/%d.%d%*s",pth_req->http_method,pth_req->http_path,&pth_req->major_version,&pth_req->minor_version)!=4){
			fclose(fr);
			strlcpy(pth_req->http_method,"GET",3);
			strlcpy(pth_req->http_path,"/500.html",9);
			pth_req->major_version = 1;
			pth_req->minor_version = 1;
			pth_req->http_response = C00_HTTP_SERVER_ERROR;
			
			return 0;
		}
		

		fclose(fr);
	}
	else{
		syslog(LOG_ERR,"I can not close fr in http_path");
		return 1;
	}

	return 0;
}
int send_http_path(struct consumer_command *tmp_cmd){
	return 0;
}
