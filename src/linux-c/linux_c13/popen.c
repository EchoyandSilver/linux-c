#include <stdio.h>
int main()
{
	FILE *fp;
	char buffer[80];
	fp = popen("cat/etc/passwd","r"); /*build I/O pipe*/
	fgets(buffer,sizeof(buffer),fp);
	printf("%s",buffer);
	pclose(fp);

}
