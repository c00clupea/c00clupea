#include "c00clupea_sim.h"

static inline int call_coreutil(int argc, char *argv[]);

int main(int argc, char *argv[]) {
	
	return call_coreutil(argc,argv);
}

int call_coreutil(int argc, char *argv[]){
	C00DEBUG("Call: %s",argv[0]);
	#ifdef C00SUNAME
	check_box(uname,"c00_uname");
	#endif
	#ifdef C00SWHOAMI
	check_box(whoami,"c00_whoami");
	#endif

	return ERROR;
	
}
