#ifndef RINGBUFFER_H
#define RINGBUFFER_H
#include <stdio.h>
#include "global.h"
#include <syslog.h>
#include <stdlib.h>
#include <limits.h>
typedef struct _ringbuffer{
	void **buffer;
	size_t element_size;
	int buffer_in;
	int buffer_out;
	int buffer_max;
}ringbuffer_t;


ringbuffer_t* init_buffer(int bufferSize, size_t element_size);
int ringbuffer_add(ringbuffer_t* buffer, void* value);
void* ringbuffer_get(ringbuffer_t* buffer);
int ringbuffer_is_full(ringbuffer_t* buffer);
int ringbuffer_is_empty(ringbuffer_t* buffer);
int destroy_ringbuffer(ringbuffer_t* buffer);

#endif
