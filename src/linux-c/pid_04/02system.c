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

int my_system(const char *command);
int main(int argc,char *argv[])
{
	
	//system("ls -l | wc -w");
	my_system("ls -l | wc -w");
	return 0;	
}
int my_system(const char *command)
{
	pid_t pid;
	int status;
	if(command == NULL)
		return -1;
	
	if((pid = fork()) < 0)
		status = -1;
	else if(pid == 0)
	{
		execl("/bin/sh","sh","-c",command,NULL);
		exit(127);
	}
	else
	{
		while(waitpid(pid,&status,0) < 0)
		{
			if(errno == EINTR)
				continue;

			status = -1;
			break;
		}
	}
	return status;
}
