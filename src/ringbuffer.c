#include "ringbuffer.h"



ringbuffer_t* init_buffer(int bufferSize, size_t element_size){
	if(bufferSize <=0){
		syslog(LOG_ERR,"ringbuffer size %d is nonsense",bufferSize);
	}
	ringbuffer_t* buffer = malloc(sizeof(ringbuffer_t));
	buffer->buffer = malloc(bufferSize * sizeof(void *));
	buffer->buffer_max = bufferSize;
	buffer->element_size = element_size;
	buffer->buffer_in = 0;
	buffer->buffer_out = 0;
	return buffer;
}

int ringbuffer_add(ringbuffer_t* buffer, void* value){
	if(buffer->buffer_in == INT_MAX){
		buffer->buffer_in = 0;
	}
	if((buffer->buffer_in - buffer->buffer_out) >= 0 && abs(buffer->buffer_in - buffer->buffer_out) < buffer->buffer_max){
	  //syslog(STDLOG,"Write to  idx %d",buffer->buffer_in % buffer->buffer_max);
		buffer->buffer[buffer->buffer_in % buffer->buffer_max] = value;
		buffer->buffer_in ++;
		return 0;
	}
	return 1;	
}
void* ringbuffer_get(ringbuffer_t* buffer){
	if(buffer->buffer_out == INT_MAX){
		buffer->buffer_out = 0;
	}
	if((buffer->buffer_in - buffer->buffer_out) > 0 && abs(buffer->buffer_in - buffer->buffer_out) < buffer->buffer_max){
	  //syslog(STDLOG,"Try to get idx %d",buffer->buffer_out % buffer->buffer_max);
		void* value = buffer->buffer[buffer->buffer_out % buffer->buffer_max];
		buffer->buffer_out ++;
		return value;
	}
	return NULL;
}
int ringbuffer_is_full(ringbuffer_t* buffer){
	if(abs(buffer->buffer_out - buffer->buffer_in) == buffer->buffer_max -1){
		return 1;
	}
	return 0;
}

int ringbuffer_is_empty(ringbuffer_t* buffer){
	if(buffer->buffer_in == buffer->buffer_out){
		return 1;
	}
	return 0;
}

int destroy_ringbuffer(ringbuffer_t* buffer){
	free(buffer->buffer);
	free(buffer);
	return 0;
}


void _test_ringbuffer(){
	ringbuffer_t *SRingBuffer = init_buffer(1024,sizeof(int));
	for(int i = 0;i < 20; i++){
		int *tmp = malloc(sizeof(int));
		*tmp = i;

		ringbuffer_add(SRingBuffer,tmp);
		syslog(STDLOG,"append to ringbuffer %d % d %d",SRingBuffer->buffer_in,SRingBuffer->buffer_out,SRingBuffer->buffer_max);	
	}
	while(!ringbuffer_is_empty(SRingBuffer)){	
		int * val = ringbuffer_get(SRingBuffer);

		syslog(STDLOG,"Wert %d",*val);
	}
	destroy_ringbuffer(SRingBuffer);

}
