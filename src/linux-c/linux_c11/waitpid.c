#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main()
{
	pid_t childpid;
	int status;
	childpid = fork();
	if(childpid < 0)
	{
		perror("failed fork()");
		exit(EXIT_FAILURE);
	}
	else if(childpid == 0)
	{
		puts("in child process");
		sleep(2);
		printf("\tchild pid = %d\n",getpid());
		printf("\tchild ppid = %d\n",getppid());
		exit(EXIT_SUCCESS);
	}else{
		waitpid(childpid,&status,0);	//等待子进程中断或结束
		puts("in parent process");
		printf("\tparent pid = %d\n",getpid());
		printf("\tparent ppid = %d\n",getppid());
		printf("\tchild process exited with status %d\n",status);
	}
	exit(EXIT_SUCCESS);
}

