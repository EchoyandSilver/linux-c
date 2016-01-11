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
	pid_t pid;
	pid = fork();
	if(pid == -1)
		ERR_EXIT("fork error");	
	
	if(pid == 0)
	{
		sleep(3);
		printf("this is child\n");
	//	exit(100);
		abort();
	}
	
	printf("this is parent\n");
	int status;
	//int ret = wait(&status);
	//int ret = waitpid(-1,&status,0);
	int ret = waitpid(pid,&status,0);
	printf("ret=%d pid=%d\n",ret,pid);
	if(WIFEXITED(&status))
		printf("child exited normal exit status=%d\n",WIFEXITED(status));
	/*	else
		printf("child exited abnormal\n");
	*/
	else if(WIFSIGNALED(status))
		printf("child exited abnormal signal number=%d\n",WTERMSIG(status));
	else if(WIFSTOPPED(status))
		printf("child stopped signal number=%d\n",WSTOPSIG(status));

	return 0;	
}
