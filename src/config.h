#ifndef CONFIG_H
#define CONFIG_H
#include <stdio.h>
#include <syslog.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"


typedef enum COMMAND_CODE{COMM_ILL=0x00,COMM_GET=0x001,COMM_SET=0x002,COMM_INIT=0x003} commandCode;
typedef enum COMMAND_TARGET_CODE{COMM_TARG_ILL=0x00,COMM_TARG_SERVER=0x001} commandTargetCode;
typedef enum TARGET_CODE{TARG_ILL=0x00,TARG_PORT=0x001,TARG_IFACE=0x002,TARG_STRATEGY=0x003,TARG_LOG=0x004} targetCode;

typedef struct _server {
	int idx;
	int iPort;
	int socket_handler;
	int strategy_idx;
	char cServerName[CONFIG_LEN];
	int log_lvl;
	struct safe_log *logger;
}server;

typedef struct _serverList{
	int iCountServer;
	server* rgServer;
}serverList;

int check_config(serverList *SServerList);
int read_config(char *cConfigPath, serverList *SServerList);
#endif
