#include "strategy_http_path.h"

static inline int _c00_receive_http_path(struct c00_consumer_command *tmp_cmd,struct c00_http_path_request *pth_req, char *log_all);
static inline int _c00_send_http_path(struct c00_consumer_command *tmp_cmd,struct c00_http_path_request *pth_req,char *log_all);
static inline int _c00_http_path_read_config(struct c00_hashmap *map);
static inline int _c00_http_path_fill_masterconfig();
static inline int _c00_http_path_write_header(FILE *fp, struct c00_http_path_request *pth_req, struct c00_http_path_single_path *pth_srq_ptr, int clen);
static inline int _c00_write_file_to_stream(FILE *fr, FILE *fp);
static inline int _c00_destroy_http_path_request(struct c00_http_path_request *pth_req);
static inline int _c00_http_path_fill_conf_htdocs(char * ident, char *val);
static inline int _c00_read_header(char *lheader, struct c00_http_path_request *pth_req, FILE *fp);
static inline int _c00_read_addr(struct c00_consumer_command *tmp_cmd, struct c00_http_path_request *pth_req);
static inline int _c00_read_header_line(char *lheader, struct c00_http_path_request *pth_req, int next_idx);
static inline int _c00_iterate_header(char *lheader,struct c00_http_path_request *pth_req, FILE *fp);

const int _c00_http_path_header_max_len = HTTP_PATH_HEADER_LINE;
const int _c00_http_path_header_max_line_len = HTTP_PATH_LINE_LEN;
pthread_mutex_t mtx_http_path_write_lock = PTHREAD_MUTEX_INITIALIZER;
const int max_http_path_line_len = HTTP_PATH_LINE_LEN;
const int max_http_path_header_len = HTTP_PATH_HEADER_LINE;



int c00_strategy_http_path(struct c00_consumer_command *tmp_cmd){
	
	struct c00_http_path_request *pth_req;
	char log_all[STD_LOG_LEN];
	pth_req = malloc(sizeof(struct c00_http_path_request));

	pth_req->header = malloc(sizeof(struct c00_array_list));
	c00_array_list_init(pth_req->header,HTTP_PATH_HEADER_LINE);

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
	struct c00_hashmap *map;

	c00_http_path_glob = malloc(sizeof(struct c00_http_path_globals));
	map = malloc(sizeof(struct c00_hashmap));
	c00_hashmap_init(map,HTTP_PATH_MAX_PATH,0);
	c00_http_path_glob->path_whitelist = map;
	
	_c00_http_path_fill_masterconfig();
	_c00_http_path_read_config(map);	

	return TRUE;
}

int _c00_destroy_http_path_request(struct c00_http_path_request *pth_req){
	c00_array_list_destroy_free(pth_req->header);
	free(pth_req);
	return TRUE;
}

int _c00_read_header(char *lheader, struct c00_http_path_request *pth_req, FILE *fp){
       	fgets(lheader,max_http_path_line_len,fp);
	if(sscanf(lheader,"%s %s HTTP/%d.%d%*s",pth_req->http_method,pth_req->http_path,&pth_req->major_version,&pth_req->minor_version)!=4){
		C00DEBUG("line %s error",lheader); 

		return FALSE;
	}
	return TRUE;
}

int _c00_read_addr(struct c00_consumer_command *tmp_cmd, struct c00_http_path_request *pth_req){
	inet_ntop(AF_INET,&(tmp_cmd->client.sin_addr),pth_req->addr,sizeof(pth_req->addr));
	return TRUE;
}

int _c00_read_header_line(char *lheader, struct c00_http_path_request *pth_req, int next_idx){
	mem_check(lheader);
	if(strstr(lheader,":")){
		struct c00_http_path_header_cmd *head_tmp = malloc(sizeof(struct c00_http_path_header_cmd));
		if(sscanf(lheader,"%s:%s",head_tmp->key,head_tmp->val) == 2){
		       	c00_array_list_set(pth_req->header,next_idx,head_tmp);
		      	return TRUE;
		}
	}
	return FALSE;
error:
	return ERROR;
}

int _c00_iterate_header(char *lheader,struct c00_http_path_request *pth_req, FILE *fp){
	int count_all;
	count_all = 0;
	while(count_all < _c00_http_path_header_max_len){
		fgets(lheader,_c00_http_path_header_max_line_len,fp);
		if(_c00_read_header_line(lheader,pth_req,count_all) == FALSE){
				break;
		}
	       	count_all ++;
	}
	return TRUE;
}


int _c00_receive_http_path(struct c00_consumer_command *tmp_cmd, struct c00_http_path_request *pth_req, char *log_all){
	FILE 	*fp;
	char 	header_line[max_http_path_line_len];

	/**open socket**/
	fp = fdopen(dup(tmp_cmd->peer_socket),"r");	

	/**test socket or jump to error**/
	check(fp,"Unable to open socket %s %d",__FILE__,__LINE__);
		
	/**increment count**/
	c00_increment_count(tmp_cmd);

	/**read addr**/
	_c00_read_addr(tmp_cmd,pth_req);

	/**read first line header and sets seek to second line**/
	if(_c00_read_header(header_line,pth_req,fp) != TRUE){
	       	strlcat(log_all,header_line,sizeof(log_all));
		fclose(fp);
		return FALSE;/**No error can be an attack or sth else...**/
	}

	/**iterate header until end or invalid and write data to struct**/
	_c00_iterate_header(header_line, pth_req, fp);

	fclose(fp);

	return TRUE;
error:
	return ERROR;
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
