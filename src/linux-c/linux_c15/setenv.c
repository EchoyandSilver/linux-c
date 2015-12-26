#include <stdio.h>  
#include <stdlib.h>

int main()
{
	char *p;
	char *test;
	if((getenv("USER")))
	printf("USER=%s\n",p);
	setenv("USER",test,1);
	printf("USER=%s\n",p);
	unsetenv("USER");
	printf("USER=%s\n",getenv("USER"));
}
