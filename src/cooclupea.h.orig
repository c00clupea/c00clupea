/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	cooclupea.h
 * created: 	Wed Sep 10 23:09:29 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */

#ifndef C00CLUPEA_H
#define C00CLUPEA_H

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
#include "util/config.h"
#include "util/ringbuffer.h"

struct c00_consumer_command{
	int peer_socket;
	struct sockaddr_in client;
  	unsigned int client_len;
  	server *serverConfig;	
};

int	main(int argc, char *argv[]);
int 	c00_increment_count(struct c00_consumer_command *cmd);

#include "strategy.h"


#endif

