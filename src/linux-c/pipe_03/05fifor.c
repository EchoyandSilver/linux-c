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
	int outfd;
	outfd = open("test02",O_WRONLY | O_CREAT | O_TRUNC,0644);
	if(outfd == -1)
		ERR_EXIT("open error");	
		
	int infd;
	infd = open("p1",O_RDONLY);
	if(infd == -1)	
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

