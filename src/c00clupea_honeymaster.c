/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 * 
 * File:	c00clupea_honeymaster.c
 * created: 	Mon Dec  1 17:31:39 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */
#include "c00clupea_honeymaster.h"

static sig_atomic_t 	is_running = 0;
static struct c00_ringbuffer *buf_rb_hmcmd;

pthread_cond_t buf_hm_not_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t buf_hm_full_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t  mtx_work_buffer_hm	= PTHREAD_MUTEX_INITIALIZER;

static inline int __initworker(pthread_t *threadpool, struct c00hm_config *config);
void *__single_worker();
static int __handle_signal(void);
static void __show_status(int sig);
static void __shutdown_regular(int sig);
static void __set_signal_mask();
static int __read_config(char *cfile, struct c00hm_config *config);
static void *__time_ticker();
static inline long __milliseconds_to_next_second();


int main( int argc, const char* argv[] ){
	
	char conffile[1024];

	if(argc<2){
		strcpy(conffile,MAINHMCONFIG);
       	} else {
		strcpy(conffile, argv[1]);
	}

	struct c00hm_config *config;
	config = malloc(sizeof(struct c00hm_config));

	check(__read_config(conffile, config),"Problem with parsing %s",conffile);
	C00DEBUG("Threads: %d",config->workerthreads);
	
	pthread_t *worker_threads;

	buf_rb_hmcmd = c00_ringbuffer_init(MAINHMCMDBUFFER,sizeof(void*));
	C00DEBUG("Start commandbuffer with size:%d",MAINHMCMDBUFFER);

	worker_threads = malloc(config->workerthreads * sizeof(pthread_t));
	check(__initworker(worker_threads,config)==TRUE,"Init for %d workerthreads failed",config->workerthreads);

	pthread_t *time_ticker = malloc(sizeof(pthread_t));
	pthread_create(time_ticker,NULL,__time_ticker,NULL);

/**#####################
 * This is a bloody Hack
 **#####################
 *  is running is hacky, but even better than join or sth else
 * <*))><
 */

	while(is_running){
		sleep(1000);
	}

	free(config);
	free(worker_threads);
	c00_destroy_ringbuffer(buf_rb_hmcmd);
	
	return TRUE;
error:
	exit(1);
}


static void *__time_ticker(){
	__set_signal_mask();
	unsigned long count = 0;
	while(is_running){
		C00DEBUG("timetick %lu",count++);
	       	if(pthread_mutex_lock(&mtx_work_buffer_hm) != 0){
			syslog(LOG_ERR,"worker not able to lock");
		}
		struct c00hm_command *tmp_cmd = malloc(sizeof(struct c00hm_command));
		tmp_cmd->command = 0x001;
		if(c00_ringbuffer_add(buf_rb_hmcmd,tmp_cmd)!= 0){
			syslog(LOG_ERR,"Sorry we can not add any cmd to ringbuffer");
		}
		C00DEBUG("Add to buffer timecommand: %d",tmp_cmd->command);
		if(pthread_cond_broadcast(&buf_hm_not_empty) != 0){
			syslog(LOG_ERR,"sorry but broadcast would not work");
		}
		if(pthread_mutex_unlock(&mtx_work_buffer_hm) != 0){
			syslog(LOG_ERR,"problem with unlock worker");
		}

		long interval = __milliseconds_to_next_second() * NANO_SECOND_MULTIPLIER;
		C00DEBUG("Waiting for %ld ns",interval);
		nanosleep((struct timespec[]){{0, interval}}, NULL);

	}
	pthread_exit((void *) 0);
	return NULL;
}


long __milliseconds_to_next_second(){
	struct timeval tv;
	gettimeofday (&tv, NULL);
	return 1000 - (tv.tv_usec / 1000);
}

int __read_config(char *cfile, struct c00hm_config *config){
	int readstat;
	mem_check(cfile);
	mem_check(config);

	dictionary *ini;

	int thread_count;
	ini = iniparser_load(cfile);
	check(ini!=NULL,"Can not parse config %s",cfile);

      	config->workerthreads =  iniparser_getint(ini, "c00clupea:threads", 4);



error:
	return ERROR;
}

int __initworker(pthread_t *threadpool, struct c00hm_config *config){
	__handle_signal();

	int worker_id = 0;
	is_running = 1;
	__handle_signal();
	C00DEBUG("Start %d Worker",config->workerthreads);

	for(worker_id = 0; worker_id < config->workerthreads; worker_id++){
		pthread_create(&threadpool[worker_id],NULL,__single_worker,NULL);
	}
	
	return TRUE;
}

void *__single_worker(){
	__set_signal_mask();
//	C00DEBUG("Started worker %s","work");
	while(is_running){
		if(pthread_mutex_lock(&mtx_work_buffer_hm) != 0){
			syslog(LOG_ERR,"worker not able to lock");
		}
		//we do sth
		while(c00_ringbuffer_is_empty(buf_rb_hmcmd)){
			if(pthread_cond_wait(&buf_hm_not_empty,&mtx_work_buffer_hm) != 0){
				syslog(LOG_ERR,"sorry but buffer not mepty makes some error in worker");
			}
		}
		struct c00hm_command *tmp_cmd = (struct c00hm_command*)c00_ringbuffer_get(buf_rb_hmcmd);
		C00DEBUG("Value for cmd: %d",tmp_cmd->command);
		if(pthread_cond_broadcast(&buf_hm_full_cond) !=0){
			syslog(LOG_ERR,"problem with broadcast in worker");
		}
		if(pthread_mutex_unlock(&mtx_work_buffer_hm) != 0){
			syslog(LOG_ERR,"problem with unlock worker");
		}


		free(tmp_cmd);

		//Here we can do sth
	}
	pthread_exit((void *)0);
	return NULL;
}

int __handle_signal(void){
	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	//shutdown
	sa.sa_handler = __shutdown_regular;
	if (sigaction(SIGTERM, &sa, NULL) == -1){
		exit(0);
	}
	if(sigaction(SIGINT, &sa,NULL) == -1){
		exit(0);
	}
	sa.sa_handler = __show_status;
	if(sigaction(SIGUSR1, &sa, NULL) == -1){
		exit(0);
	}

	return TRUE;
}

void __show_status(int sig){}

void __shutdown_regular(int sig){
       	is_running = 0;
	syslog(STDLOG,"Received signal %d......Terminating",sig);
}

void __set_signal_mask(){
	static sigset_t   signal_mask;
	//pthread_t  sig_thr_id;      
	sigemptyset(&signal_mask);
	sigaddset (&signal_mask, SIGINT);
	sigaddset (&signal_mask, SIGTERM);
	sigaddset (&signal_mask, SIGUSR1);
	sigaddset (&signal_mask, SIGUSR2);
	pthread_sigmask (SIG_BLOCK, &signal_mask, NULL);

}

