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
	umask(0);
	int fd;
	fd = open("test.txt",O_RDONLY | O_CREAT | O_EXCL,0666);
	if(fd == -1)	
		ERR_EXIT("open error");
	printf("open succ\n");
	return 0;
}
