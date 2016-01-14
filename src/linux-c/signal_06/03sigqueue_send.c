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
	if(argc != 2)
	{
		fprintf(stderr,"Usage %s pid\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	pid_t pid;
	union sigval v;
	v.sival_int = 100;
	sigqueue(pid,SIGINT,v);
	return 0;	
}

