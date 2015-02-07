/**
 *
 * cooclupea Honeypot
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	ringbuffer.c
 * created: 	Thu Sep 11 08:30:56 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */

#include "ringbuffer.h"

struct c00_ringbuffer *c00_ringbuffer_init(int bufferSize, size_t element_size)
{
    if(bufferSize <= 0) {
        syslog(LOG_ERR, "ringbuffer size %d is nonsense", bufferSize);
    }

    struct c00_ringbuffer *buffer = malloc(sizeof(struct c00_ringbuffer));

    buffer->buffer = malloc(bufferSize * sizeof(void *));

    buffer->buffer_max = bufferSize;

    buffer->element_size = element_size;

    buffer->buffer_in = 0;

    buffer->buffer_out = 0;

    return buffer;
}

int c00_ringbuffer_add(struct c00_ringbuffer *buffer, void *value)
{
    if(buffer->buffer_in == INT_MAX) {
        buffer->buffer_in = 0;
    }

    if((buffer->buffer_in - buffer->buffer_out) >= 0 && abs(buffer->buffer_in - buffer->buffer_out) < buffer->buffer_max) {
        //syslog(STDLOG,"Write to  idx %d",buffer->buffer_in % buffer->buffer_max);
        buffer->buffer[buffer->buffer_in % buffer->buffer_max] = value;
        buffer->buffer_in ++;
        return 0;
    }

    return 1;
}
void *c00_ringbuffer_get(struct c00_ringbuffer *buffer)
{
    if(buffer->buffer_out == INT_MAX) {
        buffer->buffer_out = 0;
    }

    if((buffer->buffer_in - buffer->buffer_out) > 0 && abs(buffer->buffer_in - buffer->buffer_out) < buffer->buffer_max) {
        //syslog(STDLOG,"Try to get idx %d",buffer->buffer_out % buffer->buffer_max);
        void *value = buffer->buffer[buffer->buffer_out % buffer->buffer_max];
        buffer->buffer_out ++;
        return value;
    }

    return NULL;
}
int c00_ringbuffer_is_full(struct c00_ringbuffer *buffer)
{
    if(abs(buffer->buffer_out - buffer->buffer_in) == buffer->buffer_max - 1) {
        return 1;
    }

    return 0;
}

int c00_ringbuffer_is_empty(struct c00_ringbuffer *buffer)
{
    if(buffer->buffer_in == buffer->buffer_out) {
        return 1;
    }

    return 0;
}

int c00_destroy_ringbuffer(struct c00_ringbuffer *buffer)
{
    free(buffer->buffer);
    free(buffer);
    return 0;
}

