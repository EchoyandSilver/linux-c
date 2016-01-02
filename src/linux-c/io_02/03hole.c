#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define ERR_EXIT(m) \
	do \
	{  \
		perror(m); \
		exit(EXIT_FAILURE);\
	}while(0) 

int main(int argc,char *argv[])
{
	int fd;
	fd = open("hole.txt",O_WRONLY | O_CREAT | O_TRUNC,0644);
	if(fd == -1)
		ERR_EXIT("open error");
	
	write(fd,"ABCDE",5);
	
	int ret = lseek(fd,32,SEEK_CUR);
	if(fd == -1)
		ERR_EXIT("lseek error");	

	write(fd,"hello",5);
	
	close(fd);

	return 0;
}
