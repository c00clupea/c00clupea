#include "strategy.h"


int strategy_dev_null(struct consumer_command *tmp_cmd){

	char buffer[INET_ADDRSTRLEN];
	const char* result=inet_ntop(AF_INET,&(tmp_cmd->client.sin_addr),buffer,sizeof(buffer));
	//syslog(STDLOG,"Yeehaa i got some date from %s",result);  
	while(1){
		int len = 0;
	  	char *input;
	  	if (read (tmp_cmd->peer_socket, &len, sizeof (len)) == 0){
      			break;
	  	}	
	  	input = (char*)malloc(len+1);
	  	read(tmp_cmd->peer_socket,input,len);

		char *search;
		search = input;
		int found_clrf = 0;

		while(*search != "\0"){
			if(*search == "\r"){
				if(*(search+1) == "\n"){
					found_clrf = 1;
					break;
				}
			}
			search++;
		}


	  	syslog(STDLOG,"rcv from %s len %d bytes input:%s\n",result,len,input);
	  	free(input);
		if(found_clrf == 1){
			break;
		}
	}
	syslog(STDLOG,"Strategy dev null finished");

	return 0;
}
