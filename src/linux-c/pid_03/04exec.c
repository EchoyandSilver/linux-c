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
	
	printf("Entering main ...\n");
	int ret = execl("/bin/ls","ls","-l",NULL);
	if(ret == -1)
		perror("execl error");
//	execlp("ls","ls","-l",NULL);
	printf("Entering main ...\n");
	
	return 0;	
}
