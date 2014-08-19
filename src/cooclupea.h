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



struct c00_consumer_command{
	int peer_socket;
	struct sockaddr_in client;
  	unsigned int client_len;
  	server *serverConfig;	
};

struct c00_consumer_command* c00_create_new_consumer_command(server* srv);

int c00_init_server(server *srv);
int c00_destroy_consumer_command(struct c00_consumer_command *tmp_cmd);

int c00_increment_count(struct c00_consumer_command *cmd);
struct req_count *c00_init_request_counter();
int c00_destroy_request_counter(struct req_count *tmp);



#include "strategy.h"


#endif

