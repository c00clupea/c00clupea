#include "cooclupea.h"


static int port_number = STANDARD_PORT;

static int default_strategy = STRAT_DEFAULT;

static sig_atomic_t is_running = 0;
static int tcp_backlog = TCP_BACKLOG;
static int worker_pool = WORKER_POOL;

static 	serverList *SServerList;

int main(int argc, char *argv[]);
pthread_mutex_t 	mtx_work_buffer						= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  	buf_main_consumer_full_cond    				= PTHREAD_COND_INITIALIZER;
pthread_cond_t  	buf_main_consumer_not_empty_cond			= PTHREAD_COND_INITIALIZER;

static char 		*main_config;

static ringbuffer_t 	*buf_main_consumer_command;


struct req_count *init_request_counter(){
	struct req_count *tmp;
	tmp = malloc(sizeof(struct req_count));
	tmp->count = 0;
#ifdef ATOMIC
	tmp->mtx = malloc(sizeof(pthreadmutex_t));
	pthread_mutex_init(tmp->mtx,NULL);
#endif
	return tmp;
}

int destroy_request_counter(struct req_count *tmp){
#ifdef ATOMIC
	free(tmp->mtx);
#endif
	free(tmp);
	return 0;
}

int increment_count(struct consumer_command *cmd){
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


int destroy_consumer_command(struct consumer_command *tmp_cmd){
  //Never ever free serverConfig here....you will need it
	free(tmp_cmd);
	return 0;
}

struct consumer_command* create_new_consumer_command(server* srv){
  	struct consumer_command *c_cmd = malloc(sizeof(struct consumer_command));
	c_cmd->serverConfig = srv;
	c_cmd->peer_socket = -1;  
	return c_cmd;
}


char* return_actual_time(void) {
	time_t current_time;
      	char* c_time_string;
	current_time = time(NULL);
	c_time_string = ctime(&current_time);
	return c_time_string;
}

void print_version(void) {
	fprintf(STDERR,"%s (%s) by %s\n",HONEYPOT_NAME,VERSION,AUTHOR);
	fprintf(STDERR,"<*)))><\n");
  	fprintf(STDERR,"c00 == red, Clupea == lat.:herring\n");
}

static void set_signal_mask()
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

void init_syslog(void) {
	int options;

#ifdef LOG_PERROR
	options = LOG_PERROR|LOG_PID|LOG_CONS;
#else
	options = LOG_PID|LOG_CONS;
#endif

	openlog ("pandora", options, SYSLOG);
}

void end_syslog(void) {
	closelog();
}

void shutdown_normal(int sig) {
	is_running = 0;
	syslog(STDLOG,"Received signal %d......Terminating",sig);
}

void show_status(int sig) {
	print_version();
	fprintf(STDERR,"Hallo Welt %d\n",sig);
}

void show_info(int sig){
	print_version();
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

void handle_signal(void) {
	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	//shutdown
	sa.sa_handler = shutdown_normal;
	if (sigaction(SIGTERM, &sa, NULL) == -1){
		exit(0);
	}
	if(sigaction(SIGINT, &sa,NULL) == -1){
		exit(0);
	}
	sa.sa_handler = show_status;
	if(sigaction(SIGUSR1, &sa, NULL) == -1){
		exit(0);
	}
	sa.sa_handler = show_info;
	if(sigaction(SIGUSR2, &sa, NULL) == -1){
		exit(0);
	}

}

static void* worker_operation(){
	set_signal_mask();
	
	while(is_running){
	  	if(pthread_mutex_lock(&mtx_work_buffer) != 0){
		  syslog(LOG_ERR,"consumer is not able to lock");
	  	}
		while(ringbuffer_is_empty(buf_main_consumer_command)){
	      		if(pthread_cond_wait(&buf_main_consumer_not_empty_cond,&mtx_work_buffer)!=0){
				syslog(LOG_ERR,"sorry but buffer not empty makes some error in consumer");	      
			}
		}
		struct consumer_command *tmp_cmd = (struct consumer_command*)ringbuffer_get(buf_main_consumer_command);
		if(tmp_cmd->peer_socket < 0){
			syslog(LOG_ERR,"We have a socket smaller 0 in consumer");
			destroy_consumer_command(tmp_cmd);
			continue;
		}
		if(pthread_cond_broadcast(&buf_main_consumer_full_cond)!=0){
			syslog(LOG_ERR,"problem with broadcast in consumer");
		}			
		if(pthread_mutex_unlock(&mtx_work_buffer)!=0){
			syslog(LOG_ERR,"problem with unlock in consumer");
		}
		//Here we can do sth --> dispatch to type
		int (*tmp_strat)(struct consumer_command *) = read_strategy_from_idx(tmp_cmd->serverConfig->strategy_idx);
		tmp_strat(tmp_cmd);		

		close(tmp_cmd->peer_socket);
		destroy_consumer_command(tmp_cmd);
	 }
       	syslog(STDLOG,"Exit worker");
	pthread_exit((void *) 0);
	return NULL;
}


static void *single_producer(void *srv){
	set_signal_mask();

	server *tmp_srv = (server*)srv;

	LOGGER_DEBUG(tmp_srv->logger,"Start producer at port %d with strategy %d",tmp_srv->iPort,tmp_srv->strategy_idx);

	while(is_running){
	  //int p_socket; 
		struct consumer_command *new_consumer_command = create_new_consumer_command(srv);
		new_consumer_command->client_len = sizeof(new_consumer_command->client);
		new_consumer_command->peer_socket = accept(tmp_srv->socket_handler,(struct sockaddr*)&(new_consumer_command->client),&(new_consumer_command->client_len));
		
		if(new_consumer_command->peer_socket < 0){
			syslog(LOG_ERR,"peer socket from producer is smaller 0....this is a problem...");
		}
		if(pthread_mutex_lock(&mtx_work_buffer) != 0){
			syslog(LOG_ERR,"producer is not able to lock");
		}
		while(ringbuffer_is_full(buf_main_consumer_command)){
			if(pthread_cond_wait(&buf_main_consumer_full_cond,&mtx_work_buffer) != 0){
				syslog(LOG_ERR,"producer is not able to wait for buffer full condition");
			}
		}
		if(ringbuffer_add(buf_main_consumer_command,new_consumer_command) != 0){
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


static pthread_t* init_producer(serverList *srv_list){
	
	pthread_t* threadpool = (pthread_t*)malloc(srv_list->iCountServer * sizeof(pthread_t));

	/**socket_handler = (int*)malloc(srv_list->iCountServer * sizeof(int));**/

	for(int i = 0; i < srv_list->iCountServer; i++){
		syslog(STDLOG,"Create socket at port %d",srv_list->rgServer[i].iPort);
		init_server(&srv_list->rgServer[i]);
	}

	threadpool = malloc(worker_pool * sizeof(pthread_t));



	for(int i = 0; i < srv_list->iCountServer; i++){
		srv_list->rgServer[i].idx = i;
		pthread_create(&threadpool[i],NULL,single_producer,&srv_list->rgServer[i]);
		//pthread_detach(threadpool[i]);
	}	
	
	return threadpool;
}

int init_server(server *srv) {

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

	char log_template[] = "logfile_%d.log";
	char log_full[255];
	snprintf(log_full,255,log_template,srv->iPort);

	srv->logger = init_safe_log(log_full);
	srv->logger->log_level = srv->log_lvl;
	
	srv->count = init_request_counter();
	return 0;
}

int init_manyserver(pthread_t *threadpool){
	is_running = 1;

	/**	int* socket_handler = (int*)malloc(port_len * sizeof(int));

	for(int i = 0; i < (int)port_len; i++){
		syslog(STDLOG,"Create socket at port %d",ports[i]);
		socket_handler[i] = init_server(ports[i]);
	}
**/
	threadpool = malloc(worker_pool * sizeof(pthread_t));

	handle_signal();
	  //current worker pool
        int worker_id = 0;
         //create worker pool threads
        for(worker_id = 0; worker_id < worker_pool; worker_id++){
		pthread_create(&threadpool[worker_id],NULL,worker_operation,NULL);
        }

	return 0;	
}

void print_help(void) {
	print_version();
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
	while ((c = getopt (argc, argv, ALLOWED_OPTS)) != -1)
	switch(c)
		{
		case 'V':
			print_version();
			break_command = 1;
			break;
		case 'h':
			print_help();
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

	init_syslog();
	
	syslog(STDLOG,"Pandora started at %s with pid %d and configfile %s",return_actual_time(),getpid(),main_config);

//	serverList *SServerList;
	SServerList = malloc(sizeof(serverList));
	server *SSingleServer = malloc(MAX_SERVER * sizeof(server));

 	SServerList->rgServer = SSingleServer;

	if(read_config(main_config,SServerList) != 0){
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

	if(init_strategies() != 0){
	    syslog(LOG_ERR,"Sorry but strategies init made some problems");
	    exit(1);	
	}

	buf_main_consumer_command = init_buffer(MAIN_BUFFER_LEN,sizeof(void*));

	pthread_t* consumer_threads = NULL;

	if(init_manyserver(consumer_threads) != 0){
	  syslog(LOG_ERR,"Sorry worker threads caused a problem during creation");
	  exit(1);
	}

	pthread_t* serverthreads;

	serverthreads = init_producer(SServerList); 

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
		close_safe_log(SServerList->rgServer[i].logger);
		destroy_request_counter(SServerList->rgServer[i].count);
	}

	//free the mallocs....
	//free(socket_handle);
	free(serverthreads);
	free(SSingleServer);
	free(SServerList);
//	free(consumer_threads);
	destroy_ringbuffer(buf_main_consumer_command);

	syslog(STDLOG,"Pandora ended at %s",return_actual_time());	
	end_syslog();
}
