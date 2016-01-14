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

void handler(int,siginfo_t *, void *);
int main(int argc,char *argv[])
{
	struct sigaction act;
	act.sa_sigaction = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;	

	if(sigaction(SIGINT, &act, NULL) < 0)
		ERR_EXIT("sigaction error");
	for(;;)
		pause();	
	return 0;	
}

void handler(int sig,siginfo_t *info, void *ctx)
{
	printf("recv a sig=%d data=%d data=%d\n",sig,info->si_value.sival_int,info->si_int);
}
