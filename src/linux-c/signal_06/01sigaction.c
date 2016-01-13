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

	if(sigaction(SIGINT, &act, NULL) < 0)
		ERR_EXIT("sigaction error");
	for(;;)
		pause();	
	return 0;	
}

void handler(int sig)
{
	printf("recv a sig=%d\n",sig);
}
