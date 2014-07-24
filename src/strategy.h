#ifndef STRATEGY_H
#define STRATEGY_H
#include <syslog.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "cooclupea.h"

int strategy_http_simple(struct consumer_command *tmp_cmd);

#endif
