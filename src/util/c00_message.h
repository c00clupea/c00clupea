/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	c00_message.h
 * created: 	Fri Dec  5 16:54:55 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#ifndef C00_MESSAGE_H
#define C00_MESSAGE_H
#include "../global.h"
#include <stdio.h>
#include <syslog.h>


#define T_SENDER short
#define T_COMMAND short
#define T_IDENT short

struct c00_ident {
    unsigned T_SENDER s_addr;
    unsigned T_SENDER r_addr;
    long connect_id;
};

struct c00_msg {
    struct c00_ident *connector;
    unsigned T_COMMAND cmd;
    unsigned T_IDENT seq;
};



int c00_connect_honeymaster(struct c00_ident *id);
int c00_close_honeymaster(struct c00_ident *id);
int c00_open_internalfile(struct c00_msg *msg, FILE *fd);
int c00_close_internalfile(struct c00_ident *id, FILE *fd);

#endif /* C00_MESSAGE_H */
