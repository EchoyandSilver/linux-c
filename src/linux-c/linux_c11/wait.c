#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main()
{
	pid_t pid;
	int status,i;
	if(fork() == 0){
		printf("This is the child process .pid = %d\n",getpid());
		exit(5);
	}else{
		sleep(1);
		printf("This is the parent processwait for child...\n");
		pid = wait(&status);		//等待子进程中断或者结束
		i = WEXITSTATUS(status);
		printf("child's pid = %d,exit status=%d\n",pid,i);
	}
}
