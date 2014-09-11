/**
 *
 * cooclupea Honeypot 
 * <*))><
 *
 * (C) 2014 by Christoph Pohl (c00clupea@googlemail.com)
 * released under the GPLv.2
 *
 * File:	cooclupea.c
 * created: 	Wed Sep 10 23:07:54 2014
 * author:  	Christoph Pohl <c00clupea@gmail.com>
 */

#include "cooclupea.h"

static char* 		_c00_return_actual_time(void);
static struct c00_consumer_command* _c00_create_new_consumer_command(server* srv);
static int		_c00_destroy_consumer_command(struct c00_consumer_command *tmp_cmd);
static struct c00_req_count* _c00_init_request_counter();
static int		_c00_destroy_request_counter(struct c00_req_count *tmp);
static int		_c00_init_server(server *srv);
static void		_c00_print_version(void);
static void 		_c00_set_signal_mask();
static void 		_c00_init_syslog(void);
static void 		_c00_end_syslog(void);
static void		_c00_shutdown_normal(int sig);
static void 		_c00_show_status(int sig);
static void 		_c00_show_info(int sig);
static void		_c00_handle_signal(void);
static void* 		_c00_worker_operation();
static void*		_c00_single_producer(void *srv);
static pthread_t* 	_c00_init_producer(serverList *srv_list);
static int 		_c00_init_manyserver(pthread_t *threadpool);
static void 		_c00_print_help(void);

static int 		port_number = STANDARD_PORT;
static int 		default_strategy = STRAT_DEFAULT;
static sig_atomic_t 	is_running = 0;
static int 		tcp_backlog = TCP_BACKLOG;
static int 		worker_pool = WORKER_POOL;
static serverList	*SServerList;
pthread_mutex_t 	mtx_work_buffer	= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  	buf_main_consumer_full_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t  	buf_main_consumer_not_empty_cond = PTHREAD_COND_INITIALIZER;
static char 		*main_config;
static struct c00_ringbuffer *buf_main_consumer_command;


struct c00_req_count *_c00_init_request_counter(){
	struct c00_req_count *tmp;
	tmp = malloc(sizeof(struct c00_req_count));
	tmp->count = 0;
#ifdef ATOMIC
	tmp->mtx = malloc(sizeof(pthreadmutex_t));
	pthread_mutex_init(tmp->mtx,NULL);
#endif
	return tmp;
}

int _c00_destroy_request_counter(struct c00_req_count *tmp){
#ifdef ATOMIC
	free(tmp->mtx);
#endif
	free(tmp);
	return 0;
}

int c00_increment_count(struct c00_consumer_command *cmd){
#ifdef ATOMIC
	if(pthread_mutex_lock(cmd->serverConfig->count->mtx) != 0){
		syslog(LOG_ERR,"logwriter is not able to lock");
		return 1;
	}

#endif

	cmd->serverConfig->count->count++;//When no atomic flag...this is not threadsafe...
#ifdef ATOMIC
	if(pthread_mutex_unlock(cmd->serverConfig->count->mtx)!=0){
		syslog(LOG_ERR,"problem with unlock in consumer");
		return 1;
	}
#endif
	return 0;

}


int _c00_destroy_consumer_command(struct c00_consumer_command *tmp_cmd){
  //Never ever free serverConfig here....you will need it
	free(tmp_cmd);
	return 0;
}

struct c00_consumer_command* _c00_create_new_consumer_command(server* srv){
  	struct c00_consumer_command *c_cmd = malloc(sizeof(struct c00_consumer_command));
	c_cmd->serverConfig = srv;
	c_cmd->peer_socket = -1;  
	return c_cmd;
}


char* _c00_return_actual_time(void) {
	time_t current_time;
      	char* c_time_string;
	current_time = time(NULL);
	c_time_string = ctime(&current_time);
	return c_time_string;
}

void _c00_print_version(void) {
	fprintf(STDERR,"%s (%s) by %s\n",HONEYPOT_NAME,VERSION,AUTHOR);
	fprintf(STDERR,"<*)))><\n");
  	fprintf(STDERR,"c00 == red, Clupea == lat.:herring\n");
}

void _c00_set_signal_mask()
{
	static sigset_t   signal_mask;
	//pthread_t  sig_thr_id;      
	sigemptyset(&signal_mask);
	sigaddset (&signal_mask, SIGINT);
	sigaddset (&signal_mask, SIGTERM);
	sigaddset (&signal_mask, SIGUSR1);
	sigaddset (&signal_mask, SIGUSR2);
	pthread_sigmask (SIG_BLOCK, &signal_mask, NULL);
}

void _c00_init_syslog(void) {
	int options;

#ifdef LOG_PERROR
	options = LOG_PERROR|LOG_PID|LOG_CONS;
#else
	options = LOG_PID|LOG_CONS;
#endif

	openlog ("c00clupea", options, SYSLOG);
}

void _c00_end_syslog(void) {
	closelog();
}

void _c00_shutdown_normal(int sig) {
	is_running = 0;
	syslog(STDLOG,"Received signal %d......Terminating",sig);
}

void _c00_show_status(int sig) {
	_c00_print_version();
	fprintf(STDERR,"Hallo Welt %d\n",sig);
}

void _c00_show_info(int sig){
	_c00_print_version();
	fprintf(STDERR,"Rcv sig %d",sig);
	fprintf(STDERR,"\n###########################################\n");
	fprintf(STDERR,"Stats\n");
	fprintf(STDERR,"###########################################\n");
	fprintf(STDERR,"ID\tName\tPort\tReq\n");
	server *tmp;
	for(int i = 0; i < SServerList->iCountServer;i++){
		tmp = &SServerList->rgServer[i];
		fprintf(STDERR,"%d\t%s\t%d\t%llu\n",tmp->idx,tmp->cServerName,tmp->iPort,tmp->count->count);	
	}

}

void _c00_handle_signal(void) {
	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	//shutdown
	sa.sa_handler = _c00_shutdown_normal;
	if (sigaction(SIGTERM, &sa, NULL) == -1){
		exit(0);
	}
	if(sigaction(SIGINT, &sa,NULL) == -1){
		exit(0);
	}
	sa.sa_handler = _c00_show_status;
	if(sigaction(SIGUSR1, &sa, NULL) == -1){
		exit(0);
	}
	sa.sa_handler = _c00_show_info;
	if(sigaction(SIGUSR2, &sa, NULL) == -1){
		exit(0);
	}

}

void* _c00_worker_operation(){
	_c00_set_signal_mask();
	
	while(is_running){
	  	if(pthread_mutex_lock(&mtx_work_buffer) != 0){
		  syslog(LOG_ERR,"consumer is not able to lock");
	  	}
		while(c00_ringbuffer_is_empty(buf_main_consumer_command)){
	      		if(pthread_cond_wait(&buf_main_consumer_not_empty_cond,&mtx_work_buffer)!=0){
				syslog(LOG_ERR,"sorry but buffer not empty makes some error in consumer");	      
			}
		}
		struct c00_consumer_command *tmp_cmd = (struct c00_consumer_command*)c00_ringbuffer_get(buf_main_consumer_command);
		if(tmp_cmd->peer_socket < 0){
			syslog(LOG_ERR,"We have a socket smaller 0 in consumer");
			_c00_destroy_consumer_command(tmp_cmd);
			continue;
		}
		if(pthread_cond_broadcast(&buf_main_consumer_full_cond)!=0){
			syslog(LOG_ERR,"problem with broadcast in consumer");
		}			
		if(pthread_mutex_unlock(&mtx_work_buffer)!=0){
			syslog(LOG_ERR,"problem with unlock in consumer");
		}
		//Here we can do sth --> dispatch to type
		int (*tmp_strat)(struct c00_consumer_command *) = c00_strategy_get_by_idx(tmp_cmd->serverConfig->strategy_idx);
		tmp_strat(tmp_cmd);		

		close(tmp_cmd->peer_socket);
		_c00_destroy_consumer_command(tmp_cmd);
	 }
       	syslog(STDLOG,"Exit worker");
	pthread_exit((void *) 0);
	return NULL;
}


void *_c00_single_producer(void *srv){
	_c00_set_signal_mask();

	server *tmp_srv = (server*)srv;

	LOGGER_DEBUG(tmp_srv->logger,"Start producer at port %d with strategy %d",tmp_srv->iPort,tmp_srv->strategy_idx);

	while(is_running){
	  //int p_socket; 
		struct c00_consumer_command *new_consumer_command = _c00_create_new_consumer_command(srv);
		new_consumer_command->client_len = sizeof(new_consumer_command->client);
		new_consumer_command->peer_socket = accept(tmp_srv->socket_handler,(struct sockaddr*)&(new_consumer_command->client),&(new_consumer_command->client_len));
		
		if(new_consumer_command->peer_socket < 0){
			syslog(LOG_ERR,"peer socket from producer is smaller 0....this is a problem...");
		}
		if(pthread_mutex_lock(&mtx_work_buffer) != 0){
			syslog(LOG_ERR,"producer is not able to lock");
		}
		while(c00_ringbuffer_is_full(buf_main_consumer_command)){
			if(pthread_cond_wait(&buf_main_consumer_full_cond,&mtx_work_buffer) != 0){
				syslog(LOG_ERR,"producer is not able to wait for buffer full condition");
			}
		}
		if(c00_ringbuffer_add(buf_main_consumer_command,new_consumer_command) != 0){
			syslog(LOG_ERR,"sorry but we can not add sth to ringbuffer");
		}
		if(pthread_cond_broadcast(&buf_main_consumer_not_empty_cond) != 0){
			syslog(LOG_ERR,"sorry but broadcast would not work");
		}
		if(pthread_mutex_unlock(&mtx_work_buffer)!=0){
			syslog(LOG_ERR,"norry but I can not unlock mutex");
		}
			
		//close(new_consumer_command->peer_socket);	
	}
	LOGGER_DEBUG(tmp_srv->logger,"End producer at port %d with strategy %d",tmp_srv->iPort,tmp_srv->strategy_idx);
		
	pthread_exit((void *) 0);
	return NULL;
}


pthread_t* _c00_init_producer(serverList *srv_list){
	
	pthread_t* threadpool = (pthread_t*)malloc(srv_list->iCountServer * sizeof(pthread_t));

	/**socket_handler = (int*)malloc(srv_list->iCountServer * sizeof(int));**/

	for(int i = 0; i < srv_list->iCountServer; i++){
		syslog(STDLOG,"Create socket at port %d",srv_list->rgServer[i].iPort);
		_c00_init_server(&srv_list->rgServer[i]);
	}

	for(int i = 0; i < srv_list->iCountServer; i++){
		srv_list->rgServer[i].idx = i;
		pthread_create(&threadpool[i],NULL,_c00_single_producer,&srv_list->rgServer[i]);
		//pthread_detach(threadpool[i]);
	}	
	
	return threadpool;
}

int _c00_init_server(server *srv) {

	struct sockaddr_in address;

	int socket_handle;

	int optval = 1;

	struct timeval timeout;      
    	timeout.tv_sec = 5;
    	timeout.tv_usec = 0;

	socket_handle = socket(INET_FAM,SOCK_STREAM,0);

	if (socket_handle == -1){
		syslog(LOG_ERR,"Not able to build the socket...\n");
		exit(1);
	}
	
	if(setsockopt(socket_handle, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1){
		syslog(LOG_WARNING,"Socket Options\n");
	}

	if (setsockopt (socket_handle, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,sizeof(timeout)) < 0){
        	syslog(LOG_WARNING,"Socket Options\n");
	}

    	if (setsockopt (socket_handle, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,sizeof(timeout)) < 0){
	  syslog(LOG_WARNING,"Socket Options\n");
	}

	memset(&address,0,sizeof(address));
	address.sin_family      = INET_FAM;
	address.sin_port        = htons(srv->iPort);
	address.sin_addr.s_addr = INADDR_ANY;
	
	if(bind(socket_handle, (struct sockaddr*) &address, sizeof(address)) == -1){	
		syslog(LOG_ERR,"I can not bind the socket....emergency break");
		exit(1);
	}

	if(listen(socket_handle,TCP_BACKLOG)==-1) {                                    
		syslog(LOG_ERR,"I am not able to listen to anything....emergency break");
		exit(1);
	}	
	srv->socket_handler = socket_handle;

	char log_template[] = LOG_MAIN_TEMPLATE;
	char log_full[255];
	snprintf(log_full,255,log_template,srv->iPort);

	/**syslog(STDLOG,"init %s",log_full);**/
	srv->logger = c00_init_safe_log(log_full);
	srv->logger->log_level = srv->log_lvl;
	
	srv->count = _c00_init_request_counter();
	return 0;
}

int _c00_init_manyserver(pthread_t *threadpool){
	is_running = 1;
	
//	threadpool = malloc(worker_pool * sizeof(pthread_t));

	_c00_handle_signal();
	  //current worker pool
        int worker_id = 0;
         //create worker pool threads
        for(worker_id = 0; worker_id < worker_pool; worker_id++){
		pthread_create(&threadpool[worker_id],NULL,_c00_worker_operation,NULL);
        }

	return 0;	
}

void _c00_print_help(void) {
	_c00_print_version();
	fprintf(STDERR,"USAGE: Cooclupea [OPTIONS]\n\n");
	fprintf(STDERR,"[OPTIONS] can be:\n");
	fprintf(STDERR,"-h		show some help\n");	
	fprintf(STDERR,"-V		show Version\n");
	fprintf(STDERR,"-p <port> 	set port\n");
	fprintf(STDERR,"-b <backlog>	set TCP backlog\n");
	fprintf(STDERR,"-c <file>	set config file\n");
	fprintf(STDERR,"\n\n");
	fprintf(STDERR,"Use signal SIGTERM or SIGINT for graceful shutdown\n");
	fprintf(STDERR,"Use signal SIGUSR1 for some info\n");
	fprintf(STDERR,"Use signal SIGUSR2 for statistics\n");

}


int main(int argc, char *argv[]) {
	int c;
	int break_command = 0;	
	int has_config = 0;

#ifdef USE_C00_TEST
	fprintf(STDERR,"Built with all TESTS########################");
#endif


	while ((c = getopt (argc, argv, ALLOWED_OPTS)) != -1)
	switch(c)
		{
		case 'V':
			_c00_print_version();
			break_command = 1;
			break;
		case 'h':
			_c00_print_help();
			break_command = 1;
			break;	
		case 'p':
			port_number = atoi(optarg);
			break;	
		case 'b':
			tcp_backlog = atoi(optarg);
			break;
		case 'c':
			has_config = 1;
			main_config = optarg;
			break;
		case 's':
			default_strategy = atoi(optarg);
	      		break;
		default:

			abort();
		}

	if (break_command) {
		exit(0);
	}

	if(!has_config){
		main_config = MAINCONFIG;
	}

	_c00_init_syslog();
	
	syslog(STDLOG,"c00clupea started at %s with pid %d and configfile %s",_c00_return_actual_time(),getpid(),main_config);

//	serverList *SServerList;
	SServerList = malloc(sizeof(serverList));
	server *SSingleServer = malloc(MAX_SERVER * sizeof(server));

 	SServerList->rgServer = SSingleServer;

	if(c00_config_read(main_config,SServerList) != 0){
		syslog(LOG_ERR,"error while reading config");
		exit(1);
	}

	//Overwrite defaults
	for(int i = 0; i < SServerList->iCountServer; i++){
		if(SServerList->rgServer[i].strategy_idx == -1){	
			SServerList->rgServer[i].strategy_idx = default_strategy;
		}
	}	


	/**int *socket_handle;**/

	if(c00_strategy_init() != 0){
	    syslog(LOG_ERR,"Sorry but strategies init made some problems");
	    exit(1);	
	}

	buf_main_consumer_command = c00_ringbuffer_init(MAIN_BUFFER_LEN,sizeof(void*));

	pthread_t* consumer_threads;
	consumer_threads = malloc(worker_pool * sizeof(pthread_t));

	if(_c00_init_manyserver(consumer_threads) != 0){
	  syslog(LOG_ERR,"Sorry worker threads caused a problem during creation");
	  exit(1);
	}

	pthread_t* serverthreads;

	serverthreads = _c00_init_producer(SServerList); 

	//while (is_running) {
//		fprintf(STDERR,"Read once");
	//}
	/**for(int i = 0; i < worker_pool;i++){
		pthread_join(consumer_threads[i],NULL);
		syslog(STDLOG,"joined worker %d",i);
	}
	for(int i = 0; i < SServerList->iCountServer;i++){
		pthread_join(serverthreads[i],NULL);
		syslog(STDLOG,"joined server %d",i);
	}**/
	while(is_running){
		//Boring but better then join or sth
		sleep(1000);
	}
	
	syslog(STDLOG,"Close sockets");

	for(int i = 0; i < SServerList->iCountServer;i++){
		c00_close_safe_log(SServerList->rgServer[i].logger);
		_c00_destroy_request_counter(SServerList->rgServer[i].count);
	}

	//free the mallocs....
	//free(socket_handle);
	free(serverthreads);
	free(SSingleServer);
	free(SServerList);
	free(consumer_threads);
	c00_destroy_ringbuffer(buf_main_consumer_command);

	syslog(STDLOG,"c00clupea ended at %s",_c00_return_actual_time());	
	_c00_end_syslog();
}
