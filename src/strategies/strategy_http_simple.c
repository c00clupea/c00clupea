#include "strategy_http_simple.h"

pthread_mutex_t mtx_http_simple_write_lock = PTHREAD_MUTEX_INITIALIZER;

const int max_line_length =  HTTP_SIMPLE_LINE_LEN;

int header_max_length = HTTP_SIMPLE_HEADER_LINE;

int strategy_http_simple(struct c00_consumer_command *tmp_cmd){
	if(receive_simple_http(tmp_cmd) != 0){
		syslog(LOG_ERR,"Error in recv http");
		return 1;
	}
        if(send_simple_http(tmp_cmd) != 0){
		syslog(LOG_ERR,"Error in sending some http");
		return 1;
	}
	return 0;
}

int receive_simple_http(struct c00_consumer_command *tmp_cmd){

	
	FILE *fr;
	fr = fdopen(dup(tmp_cmd->peer_socket),"r");
	char header_line[max_line_length];
	
	if(fr){

		increment_count(tmp_cmd);

		int count_all = 0;
		//fgets(header_line,max_line_length,fr);
		char buffer[INET_ADDRSTRLEN];
		const char* result=inet_ntop(AF_INET,&(tmp_cmd->client.sin_addr),buffer,sizeof(buffer));
		char log_all[STD_LOG_LEN];
		snprintf(log_all,STD_LOG_LEN,"rcv from %s count %llu:\n",result,tmp_cmd->serverConfig->count->count);
		fgets(header_line,max_line_length,fr);

		while(count_all <  header_max_length){
			
			fgets(header_line,max_line_length,fr);
			if(strstr(header_line,":")){
				//syslog(STDLOG,header_line);
				strlcat(log_all,header_line,sizeof(log_all));
				count_all++;
			}
			else{
				break;
			}
		}		
		LOGGER_INFO(tmp_cmd->serverConfig->logger,"%s",log_all);
		fclose(fr);
	}
	else{
		syslog(LOG_ERR,"I can not close fr in http_simple");
		return 1;
	}
	return 0;
}

int send_simple_http(struct c00_consumer_command *tmp_cmd){
	FILE   *fp = fdopen(dup(tmp_cmd->peer_socket),"w");
	FILE 	*fr = fopen("index.html","r");
	fprintf(fp,"HTTP/1.1 200 OK\n");
	int ch;
	if(fr){
		while((ch=getc(fr))!=EOF)  {
			fprintf(fp,"%c",ch);	
			
		}
		fclose(fr);
	}

	fclose(fp);
	return 0;
}
