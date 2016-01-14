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

void handler(int sig);
int main(int argc,char *argv[])
{
	int pipefd[2];
	if(pipe(pipefd) == -1)
		ERR_EXIT("pipe error");
	
	pid_t pid;
	pid = fork();
	if(pid == -1)
		ERR_EXIT("fork error");
	if(pid == 0)
	{
		dup2(pipefd[1],STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execlp("ls","ls",NULL);
		fprintf(stderr,"error execute ls\n");
		exit(EXIT_SUCCESS);
	}
	
	dup2(pipefd[0],STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	execlp("wc","wc","-w",NULL);
	fprintf(stderr,"error execute wc\n");
	return 0;	
}

