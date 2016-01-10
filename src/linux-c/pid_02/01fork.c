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
	signal(SIGCHLD, SIG_IGN);
	printf("before fork pid = %d\n",getpid());
	
	int fd;
	fd = open("test.txt",O_WRONLY);
	if(fd == 1)
		ERR_EXIT("open error");

	pid_t pid;
	pid = fork();
	if(pid == -1)
		ERR_EXIT("fork error");

	if(pid > 0)
	{
		printf("parent pid=%d child pid=%d\n",getpid(),pid);
		write(fd,"parent",6);
		sleep(3);
	}
	else if(pid == 0)
	{
		printf("child pid=%d parent pid=%d\n",getpid(),getppid());
		write(fd,"child",5);
	}	

	return 0;	
}
