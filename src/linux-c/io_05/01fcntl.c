#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

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

int main(int argc,char *argv[])
{
	int fd;
	fd = open("test.txt",O_WRONLY);	
	if(fd == -1)
		ERR_EXIT("open error");
/*	
	close(1);
	dup(fd);
*/
/*
	dup2(fd,1);
*/
	close(1);	
	if((fcntl(fd,F_DUPFD,0)) < 0)	
		ERR_EXIT("dup fd error");

	printf("hello\n");
	return 0;	
}
