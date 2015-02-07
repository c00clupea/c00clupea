#ifndef RINGBUFFER_H
#define RINGBUFFER_H
#include <stdio.h>
#include "global.h"
#include <syslog.h>
#include <stdlib.h>
#include <limits.h>
struct c00_ringbuffer{
	void **buffer;
	size_t element_size;
	int buffer_in;
	int buffer_out;
	int buffer_max;
};


struct c00_ringbuffer* 	c00_ringbuffer_init(int bufferSize, size_t element_size);
int 		c00_ringbuffer_add(struct c00_ringbuffer* buffer, void* value);
void* 		c00_ringbuffer_get(struct c00_ringbuffer* buffer);
int 		c00_ringbuffer_is_full(struct c00_ringbuffer* buffer);
int 		c00_ringbuffer_is_empty(struct c00_ringbuffer* buffer);
int 		c00_destroy_ringbuffer(struct c00_ringbuffer* buffer);

#endif
