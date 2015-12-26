#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *p;
	if((p = getenv("USER")))
	printf("USER=%s\n",p);
	putenv("User=test");
	printf("USER=%s\n",getenv("USER"));
}
