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

int gval = 100;
int main(int argc,char *argv[])
{
	signal(SIGCHLD, SIG_IGN);
	printf("before fork pid = %d\n",getpid());
	pid_t pid;
	pid = vfork();
	if(pid == -1)
		ERR_EXIT("fork error");

	if(pid > 0)
	{
		printf("parent pid=%d child pid=%d gval=%d\n",getpid(),pid,gval);
	}
	else if(pid == 0)
	{
		char *const args[] = {"ps",NULL};
		execve("/bin/ps",args,NULL);
		gval++;
		printf("child pid=%d parent pid=%d gval=%d\n",getpid(),getppid(),gval);
	}	

	return 0;	
}
