#include "strategy_http_path.h"

static int _c00_destroy_http_path_request(struct c00_http_path_request *pth_req);
static int _c00_receive_http_path(struct c00_consumer_command *tmp_cmd,struct c00_http_path_request *pth_req, char *log_all);
static int _c00_send_http_path(struct c00_consumer_command *tmp_cmd,struct c00_http_path_request *pth_req,char *log_all);
static int _c00_http_path_read_config(struct c00_hashmap *map);
static int _c00_http_path_fill_masterconfig();
static int _c00_http_path_fill_conf_htdocs(char * ident, char *val);
static int _c00_http_path_write_header(FILE *fp, struct c00_http_path_request *pth_req, struct c00_http_path_single_path *pth_srq_ptr, int clen);
static int _c00_write_file_to_stream(FILE *fr, FILE *fp);
static int _c00_read_header(char *lheader, struct c00_http_path_request *pth_req);
static int _c00_write_addr_to_str(char *log_all, struct c00_consumer_command *tmp_cmd);

const int _c00_http_path_header_max_len = HTTP_PATH_HEADER_LINE;
const int _c00_http_path_header_max_line_len = HTTP_PATH_LINE_LEN;

pthread_mutex_t mtx_http_path_write_lock = PTHREAD_MUTEX_INITIALIZER;

const int max_http_path_line_len = HTTP_PATH_LINE_LEN;

const int max_http_path_header_len = HTTP_PATH_HEADER_LINE;



int c00_strategy_http_path(struct c00_consumer_command *tmp_cmd){
	
	struct c00_http_path_request *pth_req;
	char log_all[STD_LOG_LEN];
	pth_req = malloc(sizeof(struct c00_http_path_request));

	int result = 0;

	if(_c00_receive_http_path(tmp_cmd,pth_req,log_all) != TRUE){
		syslog(LOG_ERR,"Error in recv http");
		result = 1;
	}
        if(_c00_send_http_path(tmp_cmd,pth_req,log_all) != TRUE){
		syslog(LOG_ERR,"Error in sending some http");
		result = 1;
	}
	LOGGER_INFO(tmp_cmd->serverConfig->logger,"%s",log_all);
     	_c00_destroy_http_path_request(pth_req);
	return result;
}

int _c00_http_path_read_config(struct c00_hashmap *map){
	FILE *fp;

	char path[PATH_MAX];
	
	c00_util_create_config_path(path,"http_path_whitelist.config");

	fp = fopen(path,"r");

	if(!fp){
		syslog(LOG_ERR,"Unable to open %s",path);
		return FALSE;
	}
	char line[HTTP_PATH_LINE_LEN + PATH_MAX + 200];
	char http_path[HTTP_PATH_LINE_LEN]; //will be copied
	char read_path[PATH_MAX];
	char mime [HTTP_PATH_MIME_LEN];
	int header_strat = 0;
	while(fgets(line,sizeof(line),fp) != NULL){

		if(sscanf(line,"%s %s %d %s",http_path,read_path, &header_strat, mime) != 4){
			syslog(LOG_ERR,"[%s] not valid",line);
			C00DEBUG("[%s] is problematic",line);
		}
		else{
//			char *target_path = malloc(PATH_MAX * sizeof(char));
			struct c00_http_path_single_path *ptr_spath = malloc(sizeof(struct c00_http_path_single_path));
			C00DEBUG("found read_path %s",read_path);
			snprintf(ptr_spath->path,PATH_MAX,"%s/%s",c00_http_path_glob->htdocs_root,read_path);
			C00DEBUG("add %s --> %s",http_path,ptr_spath->path);
			ptr_spath->header_strategy = header_strat;
			C00DEBUG("add %s --> strat %d",http_path,ptr_spath->header_strategy);
			strlcpy(ptr_spath->mime,mime,HTTP_PATH_MIME_LEN);
			C00DEBUG("Found mime %s",ptr_spath->mime);
			c00_hashmap_add_key_value(map,http_path,sizeof(http_path),ptr_spath);
			C00DEBUG("add %s --> %s",http_path,ptr_spath->path);
		}
			
	}
	fclose(fp);
	return TRUE;
}

int _c00_http_path_fill_conf_htdocs(char * ident, char *val){
	if(strcmp(ident, "htdocs") == 0){
		C00DEBUG("found htdocs with %s",val);
		strlcpy(c00_http_path_glob->htdocs_root,val,PATH_MAX);
		return TRUE;
	}
	return FALSE;
}

int _c00_http_path_fill_masterconfig(){
	FILE *fp;

	char path[PATH_MAX];

	char ident[PATH_MAX];
	char val[PATH_MAX];

	
	c00_util_create_config_path(path,"http_path_master.config");

	fp = fopen(path,"r");

	if(!fp){
		syslog(LOG_ERR,"unable to open %s",path);
		return FALSE;
	}
	char line[(2 * PATH_MAX) + 1];

	while(fgets(line,((2 * PATH_MAX) + 1),fp) != NULL){
		if(sscanf(line, "%s %s",ident, val) != 2){
			syslog(LOG_ERR,"[%s] not valid",line);
			C00DEBUG("[%s] is problematic",line);
		}
		else{
			if(_c00_http_path_fill_conf_htdocs(ident,val) == TRUE){
				continue;
			}
		}
	}
	
	return TRUE;
}

int c00_strategy_http_path_init(){
	c00_http_path_glob = malloc(sizeof(struct c00_http_path_globals));
	struct c00_hashmap *map;
	map = malloc(sizeof(struct c00_hashmap));
	c00_hashmap_init(map,HTTP_PATH_MAX_PATH,0);

	c00_http_path_glob->path_whitelist = map;
	_c00_http_path_fill_masterconfig();
	_c00_http_path_read_config(map);	

	return TRUE;
}

int _c00_destroy_http_path_request(struct c00_http_path_request *pth_req){
	free(pth_req);
	return 0;
}

int _c00_read_header(char *lheader, struct c00_http_path_request *pth_req){
	if(sscanf(lheader,"%s %s HTTP/%d.%d%*s",pth_req->http_method,pth_req->http_path,&pth_req->major_version,&pth_req->minor_version)!=4){
		C00DEBUG("line %s error",lheader); 

		return FALSE;
	}
	return TRUE;
}

int _c00_write_addr_to_str(char *log_all, struct c00_consumer_command *tmp_cmd){
	char 	buffer[INET_ADDRSTRLEN];
	const char* result=inet_ntop(AF_INET,&(tmp_cmd->client.sin_addr),buffer,sizeof(buffer));
	
	snprintf(log_all,STD_LOG_LEN,"rcv from %s count %llu:\n",result,tmp_cmd->serverConfig->count->count);
	return TRUE;
}

int _c00_receive_http_path(struct c00_consumer_command *tmp_cmd, struct c00_http_path_request *pth_req, char *log_all){
	FILE 	*fp;
	char 	header_line[max_http_path_line_len];

	int 	count_all;

	count_all = 0;

	fp = fdopen(dup(tmp_cmd->peer_socket),"r");	

	if(!fp){
		syslog(LOG_ERR,"Unable to open socket");
		return ERROR;
	}
		
	c00_increment_count(tmp_cmd);

	_c00_write_addr_to_str(log_all,tmp_cmd);

	/**read the first line**/
	fgets(header_line,max_http_path_line_len,fp);

	strlcat(log_all,header_line,sizeof(log_all));

	if(_c00_read_header(header_line,pth_req) != TRUE){
		fclose(fp);
		return FALSE;
	}

	while(count_all < _c00_http_path_header_max_len){
		fgets(header_line,_c00_http_path_header_max_line_len,fp);
		if(strstr(header_line,":")){
			strlcat(log_all,header_line,sizeof(log_all));
			count_all ++;
		}
		else{
			break;
		}
	}

	fclose(fp);
	

	return TRUE;
}

int _c00_http_path_write_header(FILE *fp, struct c00_http_path_request *pth_req, struct c00_http_path_single_path *pth_srq_ptr, int flen){
	if(pth_srq_ptr->header_strategy == HTTP_PATH_STRATEGY_PLAIN){
		C00DEBUG("file header strat %d",pth_srq_ptr->header_strategy);
		return TRUE;
	}
	if(pth_srq_ptr->header_strategy == HTTP_PATH_STRATEGY_OK){
		C00DEBUG("file header strat %d",pth_srq_ptr->header_strategy);
		fprintf(fp,"%s","HTTP/1.1 200 OK\r\n");
		char timebuffer[30];
		time_t now = 0;
		struct tm *t;
		now = time(NULL);
		t = gmtime(&now);
		strftime(timebuffer,30,"%a, %d %b %Y %H:%M:%S %Z",t);
		fprintf(fp,"%s:%s\r\n","DATE",timebuffer);
		fprintf(fp,"%s:%s\r\n","SERVER","c00clupea");
		fprintf(fp,"%s:%s\r\n","Content-Type",pth_srq_ptr->mime);
		fprintf(fp,"%s: %d\r\n","Content-Length",flen);
		fprintf(fp,"\n");
		return TRUE;
	}
	C00DEBUG("no header strategy found for %d",pth_srq_ptr->header_strategy);
	return FALSE;	
}

static int _c00_write_file_to_stream(FILE *fr, FILE *fp){
	char ch;
	while((ch=getc(fr))!=EOF){
	      	fprintf(fp,"%c",ch);
	}
	return TRUE;
}

int _c00_send_http_path(struct c00_consumer_command *tmp_cmd,struct c00_http_path_request *pth_req,char *log_all){
	FILE *fr;
	FILE *fp;		
	fp = fdopen(dup(tmp_cmd->peer_socket),"w");
	struct c00_http_path_single_path *path_to_get;
	int flen = 0;
	if(!fp){
		return FALSE;
	}
	else{
		if(c00_hashmap_get_value(c00_http_path_glob->path_whitelist,pth_req->http_path,HTTP_PATH_LINE_LEN,(void *)&path_to_get) == FALSE)
		{
			//Here is some 404
		}
		else{
			fr = fopen(path_to_get->path,"r");
			
			flen = c00_util_file_size(path_to_get->path);				
			C00DEBUG("try to read %s",path_to_get->path);
			if(!fr){
				syslog(LOG_ERR,"Sorry file %s not exists",path_to_get->path);
						
			}
			else{
				_c00_http_path_write_header(fp, pth_req, path_to_get,flen);		
				_c00_write_file_to_stream(fr,fp);

				fclose(fr);
				

			}
		}

	 fclose(fp);	
	}

	return TRUE;
}
