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
int main(int argc,char *argv[])
{
	struct sigaction act;
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;	

	sigset_t s;
	sigemptyset(&s);
	sigaddset(&s,SIGINT);
	sigaddset(&s,SIGRTMIN+1);
	sigprocmask(SIG_BLOCK,&s,NULL);
	if(sigaction(SIGINT, &act, NULL) < 0)
		ERR_EXIT("sigaction error");
	if(sigaction(SIGRTMIN, &act, NULL) < 0)
		ERR_EXIT("sigaction error");
	if(sigaction(SIGUSR1, &act, NULL) < 0)
		ERR_EXIT("sigaction error");
	for(;;)
		pause();	
	return 0;	
}

void handler(int sig)
{
	if(sig == SIGINT || sig == SIGRTMIN)
		printf("recv a sig=%d\n",sig);
	else if(sig == SIGUSR1)
	{
		sigset_t s;
		sigemptyset(&s);
		sigaddset(&s,SIGINT);
		sigaddset(&s,SIGRTMIN+1);
		sigprocmask(SIG_UNBLOCK,&s,NULL);
	}
}
