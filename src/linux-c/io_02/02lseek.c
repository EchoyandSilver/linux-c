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
	
	fd = open(argv[0],O_RDONLY);
	if(fd == -1)
		ERR_EXIT("open error");

	char buf[1024] = {0};
	int ret = read(fd,buf,5);
	if(fd == -1)
		ERR_EXIT("read error");
	printf("buf = %s\n",buf);	

	ret = lseek(fd,0,SEEK_CUR);
	if(fd == -1)	
		ERR_EXIT("lseek");

	printf("current offset=%d\n",ret);
	return 0;
}
