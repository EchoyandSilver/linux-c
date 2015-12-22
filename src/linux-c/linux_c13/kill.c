#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	int status;
	if(!(pid = fork()))
	{
		printf("this is a child process");
		sleep(10);
		return;
	}else{
		printf("send signal to child process(%d)\n",pid);
		sleep(1);
		kill(pid,SIGABRT); /*send signal to the pid*/
		wait(&status);
		if(WIFSIGNALED(status))
		printf("child process receive signal %d\n",WTERMSIG(status));
	}
}
