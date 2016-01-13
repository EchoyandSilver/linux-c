#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define ERR_EXIT(m) \
	do \
	{	\
		perror(m);\
		exit(EXIT_FAILURE);\
	}while(0)

void handler(int sig);
__sighandler_t my_signal(int sig, __sighandler_t handler);
int main(int argc,char *argv[])
{
/*
	struct sigaction act;
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;	

	if(sigaction(SIGINT, &act, NULL) < 0)
		ERR_EXIT("sigaction error");
*/
	my_signal(SIGINT,handler);
	for(;;)
		pause();	
	return 0;	
}

__sighandler_t my_signal(int sig, __sighandler_t handler)
{
	struct sigaction act;
	struct sigaction oldact;
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	
	if(sigaction(sig,&act,&oldact) < 0)
		return SIG_ERR;
	return oldact.sa_handler;
}
void handler(int sig)
{
	printf("recv a sig=%d\n",sig);
}
