#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler()
{
	printf("hello\n");
}

int main()
{
	int i;
	signal(SIGALRM,handler);
	alarm(5);	/* set alarm of signal */
	for(i=0;i<7;i++)
	{
		printf("sleep %d ...\n",i);
		sleep(1);
	}
}

