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
	int fd;
/*	fd = open("p1",O_WRONLY);	*/
	fd = open("p1",O_WRONLY | O_NONBLOCK);
	if(fd == -1)
		ERR_EXIT("open error");	
	
	printf("open succ\n");
	return 0;	
}

