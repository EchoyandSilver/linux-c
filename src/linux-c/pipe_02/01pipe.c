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
		sleep(3);
		close(pipefd[0]);
		write(pipefd[1],"hello",5);
		close(pipefd[1]);
		exit(EXIT_SUCCESS);
	}
	
	close(pipefd[1]);
	char buf[10] = {0};
	int flags = fcntl(pipefd[0],F_GETFL);
	fcntl(pipefd[0],F_SETFL,flags | O_NONBLOCK);
	int ret = read(pipefd[0],buf,10);
	if(ret == -1)
		ERR_EXIT("read error");
	printf("buf = %s\n",buf);
	return 0;	
}

