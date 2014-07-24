#ifndef PANDORA_H
#define PANDORA_H

#include <stdio.h>
#include <syslog.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/types.h>
#include "global.h"
#include "config.h"
#include "ringbuffer.h"


struct consumer_command{
	int peer_socket;
	struct sockaddr_in client;
  	unsigned int client_len;
  	server *serverConfig;	
};

struct consumer_command* create_new_consumer_command(server* srv);

int init_server(server *srv);
int destroy_consumer_command(struct consumer_command *tmp_cmd);

#include "strategy.h"
#include "strategy_dev_null.h"

#endif

