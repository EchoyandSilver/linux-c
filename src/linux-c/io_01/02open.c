#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
#define ERR_EXIT(m) (perror(m),exit(EXIT_FAILURE))
*/

#define ERR_EXIT(m) \
	do \
	{  \
		perror(m); \
		exit(EXIT_FAILURE);\
	}while(0) 

int main(void)
{
	int fd;
	fd = open("test.txt",O_RDONLY);
/*
	if(fd == -1)
	{
		fprintf(stderr,"open error with errno=%d %s\n",
		errno,strerror(errno));
		exit(EXIT_FAILURE);
	}
*/
/*
	if(fd == -1)
	{
		perror("open error");
		exit(EXIT_FAILURE);
	}
*/
	if(fd == -1)	
		ERR_EXIT("open error");
	printf("open succ\n");
	return 0;
}
