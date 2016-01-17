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
	mkfifo("p1",0644);
	int infd;
	infd = open("test",O_RDONLY);
	if(infd == -1)
		ERR_EXIT("open error");	
		
	int outfd;
	outfd = open("p1",O_WRONLY);
	if(outfd == -1)	
		ERR_EXIT("open error");

	char buf[1024];
	int n;
	while(( n = read(infd,buf,1024)) > 0)
	{
		write(outfd,buf,n);
	}
	
	close(infd);
	close(outfd);
	return 0;	
}

