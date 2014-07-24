#include "strategy_http_simple.h"

pthread_mutex_t mtx_http_simple_write_lock = PTHREAD_MUTEX_INITIALIZER;

const int max_line_length = 8 * 1024;//8KB

FILE	*log_file;

int header_max_length = 128;

int init_http_simple_log(){
	log_file = fopen("simple_http_log.log","w");
	if(!log_file){
		return 1; 
	}
	return 0;
}

int destroy_http_simple_log(){
	if(log_file){
		fclose(log_file);
	}
}

int print_http_simple_log()
{
	int res = 0;
	if(pthread_mutex_lock(&mtx_http_simple_write_lock) != 0){
		syslog(LOG_ERR,"logwriter is not able to lock");
		return 1;
	}

	if(pthread_mutex_unlock(&mtx_http_simple_write_lock)!=0){
		syslog(LOG_ERR,"problem with unlock in consumer");
		return 1;
	}
	return res;

}

int strategy_http_simple(struct consumer_command *tmp_cmd){
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

int receive_simple_http(struct consumer_command *tmp_cmd){

	
	FILE *fr;
	fr = fdopen(dup(tmp_cmd->peer_socket),"r");
	char header_line[max_line_length];

	if(fr){

		int count_all = 0;
		fgets(header_line,max_line_length,fr);
		char buffer[INET_ADDRSTRLEN];
		const char* result=inet_ntop(AF_INET,&(tmp_cmd->client.sin_addr),buffer,sizeof(buffer));
		while(count_all <  header_max_length
)
		syslog(STDLOG,"recv at port %d from %s input %s",tmp_cmd->serverConfig->iPort,result,header_line);
		
	}
	fclose(fr);
	return 0;
}

int send_simple_http(struct consumer_command *tmp_cmd){
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
