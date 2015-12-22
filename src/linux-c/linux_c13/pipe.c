#include <stdio.h>
#include <unistd.h>

int main()
{
	int filedes[2];
	char buffer[80];
	pipe(filedes);
	if(fork()>0)
	{
		/*parent process*/
		char s[] = "hello!\n";
		write(filedes[1],s,sizeof(s));
	}else{
		/*child process*/
		read(filedes[0],buffer,80);
		printf("%s",buffer);
	}
}
