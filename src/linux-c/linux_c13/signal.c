#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler(int signo)
{	
	if(signo == SIGINT)	
		puts("catch the SIGINT");
	else if(signo == SIGQUIT)
		puts("catch the SIGQUIT");
}

int main(int argc, const char *argv[])
{
	/*set the signal*/
	signal(SIGINT,handler);
	signal(SIGQUIT,handler);

	while(1)
	{
		sleep(1);
		puts("hello world");
	}
	
}
