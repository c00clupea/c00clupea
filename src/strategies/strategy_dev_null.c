/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	strategy_dev_null.c
 * created: 	Thu Sep 11 08:34:36 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */

#include "strategy_dev_null.h"

int c00_strategy_dev_null(struct c00_consumer_command *tmp_cmd)
{
    char buffer[INET_ADDRSTRLEN];
    const char *result = inet_ntop(AF_INET, &(tmp_cmd->client.sin_addr), buffer, sizeof(buffer));
    int len = 1024;
    char *input;
    input = (char *)malloc(len + 1);
    read(tmp_cmd->peer_socket, input, len);
    syslog(STDLOG, "rcv from %s at port %d tmp_cmd len %d bytes input:%s\n", result, tmp_cmd->serverConfig->iPort, len, input);
    free(input);
    syslog(STDLOG, "Strategy dev null finished");
    return 0;
}
