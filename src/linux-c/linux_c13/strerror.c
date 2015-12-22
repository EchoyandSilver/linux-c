#include <string.h>
#include <stdio.h>

int main()
{
	int i;
	for(i=0;i<10;i++)
	printf("%d : %s \n",i,strerror(i)); /*return the strerror of the str*/
}
