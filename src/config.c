#include "config.h"

void read_server_name(char *line,char* cServerName){
	char n1[CONFIG_LEN];
	char n2[CONFIG_LEN];
	char server_name_hold[CONFIG_LEN];

	if(sscanf(line, "%s %s %s %*s",n1,n2,server_name_hold) != 3){
		syslog(LOG_ERR,"wrong params for init");
		exit(1);
	}
	strcpy(cServerName,server_name_hold);
}

void read_server_strategy(char *line, int *strategy){
	char n1[CONFIG_LEN];
	char n2[CONFIG_LEN];
	char n3[CONFIG_LEN];
	char n4[CONFIG_LEN];
	if(sscanf(line, "%s %s %s %s %d",n1,n2,n3,n4,strategy) != 5){
		syslog(LOG_ERR,"wrong params for strategy");
		exit(1);
	}
}

void read_server_port(char *line,int *port){
	char n1[CONFIG_LEN];
	char n2[CONFIG_LEN];
	char n3[CONFIG_LEN];
	char n4[CONFIG_LEN];
	if(sscanf(line, "%s %s %s %s %d",n1,n2,n3,n4,port) != 5){
		syslog(LOG_ERR,"wrong params for init");
		exit(1);
	}
	
}

targetCode read_result_target_code(commandTargetCode command_target_code,char *line){
	char n1[CONFIG_LEN];
	char n2[CONFIG_LEN];
	char n3[CONFIG_LEN];
	char target[CONFIG_LEN];
	targetCode target_code = TARG_ILL;
	if(sscanf(line,"%s %s %s %s %*s",n1,n2,n3,target) != 4){
		syslog(LOG_ERR,"wrong params for command target");
		exit(1);
	}
	if(command_target_code == COMM_TARG_SERVER){
		if(strcmp(target,"port") == 0){
			target_code = TARG_PORT;
		}
		else if (strcmp(target,"iface") == 0){
			target_code = TARG_IFACE;
		}
		else if (strcmp(target,"strategy") == 0){
			target_code = TARG_STRATEGY;
		}
		else {
			syslog(LOG_ERR,"sorry target not found");
			exit(1);
		}
	} else {
		syslog(LOG_ERR,"sorry but for this command target there is no target available");
		exit(1);
	}
	return target_code;
}

commandTargetCode read_target(commandCode command_code,char *line){
	char n1[CONFIG_LEN];
	commandTargetCode target_code = COMM_TARG_ILL;
	char target[CONFIG_LEN];
	if (sscanf(line,"%s %s %*s",n1,target) != 2){
		syslog(LOG_ERR,"wrong params for command");
		exit(1);
	}
	if(command_code == COMM_SET || command_code == COMM_INIT){
		//syslog(STDLOG,"found target '%s'",target);
		if(strcmp(target,"server") == 0){
			target_code = COMM_TARG_SERVER;
		}
		else{
			syslog(LOG_ERR,"Sorry command target not found");
			exit(1);
		}
	}
	return target_code;
}

commandCode read_command(char *line){
	commandCode command_code = COMM_ILL;
	char command[CONFIG_LEN];
	if(sscanf(line,"%s %*s",command)==1){
		if(strcmp(command,"set") == 0){
			command_code = COMM_SET;
		}
		else if(strcmp(command,"get") == 0){
			command_code = COMM_GET;
		}
		else if(strcmp(command,"init") == 0){
			command_code = COMM_INIT;
		}
		else{
			syslog(LOG_ERR,"Command not found");
			exit(1);
		}

	}
	return command_code;
}

server* find_server_by_name(char *cServerName, serverList *SServerList){
	for(int i = 0;i < SServerList->iCountServer;i++){
		if(strcmp(SServerList->rgServer[i].cServerName,cServerName) == 0){
			return &SServerList->rgServer[i];
		}
	}
	return NULL;
}

void write_strategy_to_server_in_struct(serverList *SServerList, char *line){
	char rgServerName[CONFIG_LEN];
	read_server_name(line,rgServerName);
	server* SSingleServer = find_server_by_name(rgServerName,SServerList);
	if(SSingleServer == NULL){
		syslog(LOG_ERR,"Sorry but Server %s is not defined, but you tried to configure a port on it",rgServerName);
		exit(1);
	}
	int *strategy = malloc(sizeof(int));
	read_server_strategy(line,strategy);
	SSingleServer->strategy_idx = *strategy;
	free(strategy);
}

void write_port_to_server_in_struct(serverList *SServerList,char* line){
	//init server
	char rgServerName[CONFIG_LEN];
	read_server_name(line,rgServerName);
	server* SSingleServer = find_server_by_name(rgServerName,SServerList);
	if(SSingleServer == NULL){
		syslog(LOG_ERR,"Sorry but Server %s is not defined, but you tried to configure a port on it",rgServerName);
		exit(1);
	}
	int *port = malloc(sizeof(int));
	read_server_port(line,port);
	SSingleServer->iPort = *port;
	free(port);

}

void write_init_config_to_Server(server *single_server){
	single_server->iPort = 0;
	single_server->socket_handler = -1;
	single_server->strategy_idx = -1;
}

void write_server_to_struct(serverList *SServerList,char* line){
	//init server
	char rgServerName[CONFIG_LEN];
	read_server_name(line,rgServerName);

	if(find_server_by_name(rgServerName,SServerList) == NULL){
		SServerList->iCountServer++;
		strcpy(SServerList->rgServer[SServerList->iCountServer-1].cServerName,rgServerName);		
		write_init_config_to_Server(&SServerList->rgServer[SServerList->iCountServer-1]);
	}
	else{
		syslog(LOG_ERR,"Sorry but Server %s is already initialized",rgServerName);
		exit(1);
	}
	
}

int check_config(serverList *SServerList){
	int result = 0;
	
	if(SServerList->iCountServer == 0){
		syslog(LOG_ERR,"no server configured");
		return 1;//Abort criteria
	}
	for(int i = 0; i < SServerList->iCountServer; i++){
		//TODO check name...
		if(SServerList->rgServer[i].iPort < 1 || SServerList->rgServer[i].iPort > 65535 ){
			syslog(LOG_ERR,"port %d for server %s is not valid",SServerList->rgServer[i].iPort,SServerList->rgServer[i].cServerName);
			result = 1;//This is bad, but one can see more errors for convienience
		}
		if(SServerList->rgServer[i].strategy_idx >= STRAT_LEN){
			syslog(LOG_ERR,"strategy is out of bound");
			result = 1;
		}
	}
	return result;
}

int read_config(char *cConfigPath, serverList *SServerList) {

	SServerList->iCountServer = 0;
	
	FILE *config_file = fopen(cConfigPath,"r");

	syslog(STDLOG,"open config %s as master config",cConfigPath);

	if(config_file == NULL){
		syslog(LOG_ERR,"I am so sorry but %s is not there or I can not open it....",cConfigPath);
		exit(1);
	}

	char line[CONFIG_LEN];

	while (fgets(line,sizeof(line),config_file) != NULL){
		commandCode command_code = read_command(line);
		if(command_code != COMM_ILL){
			commandTargetCode target_code = read_target(command_code,line);
			if(command_code == COMM_INIT && target_code == COMM_TARG_SERVER){
				write_server_to_struct(SServerList,line);
			}
			else if(command_code == COMM_SET && target_code == COMM_TARG_SERVER){
				targetCode result_target_code = read_result_target_code(target_code,line);
				if(result_target_code == TARG_PORT){
					write_port_to_server_in_struct(SServerList,line);					
				}
				if(result_target_code == TARG_STRATEGY){
					write_strategy_to_server_in_struct(SServerList,line);
				}
			}	
		}
	}
	fclose(config_file);
	return check_config(SServerList);
}


