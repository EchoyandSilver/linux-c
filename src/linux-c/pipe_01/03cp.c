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

int main(int argc,char *argv[])
{
	close(0);
	open("test",O_RDONLY);
	close(1);
	open("test01",O_WRONLY | O_CREAT | O_TRUNC , 0644);
	
	execlp("cat","cat",NULL);	

	return 0;	
}

