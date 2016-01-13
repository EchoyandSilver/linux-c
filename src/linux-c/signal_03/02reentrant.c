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

typedef struct
{
	int a;
	int b;
}TEST;

TEST g_data;

void handler(int sig);
int main(int argc,char *argv[])
{
	TEST zeros = {0,0};
	TEST ones = {1,1};
	if(signal(SIGALRM, handler) == SIG_ERR)
		ERR_EXIT("signal error");
	
	g_data = zeros;
	alarm(1);
	for(;;)
	{
		g_data = zeros;
		g_data = ones;	
	}		
	return 0;	
}

void unsafe_fun()
{
	printf("%d %d\n",g_data.a,g_data.b);
}

void handler(int sig)
{
	unsafe_fun();
	alarm(1);
}
