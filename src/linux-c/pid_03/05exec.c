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
	char *const envp[] = {"AA=11","BB=22",NULL};
//	int ret = execl("./hello","hello",NULL);
	int ret = execle("./hello","hello",NULL,envp);
	if(ret == -1)
		perror("execl error");
	printf("Entering main ...\n");
	
	return 0;	
}
