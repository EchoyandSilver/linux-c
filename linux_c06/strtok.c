#include <string.h>

int main()
{
	//分割字符串
	char s[]="ab-cd : ef;gh : i-jkl;qrs-tu: vwx-y;z";
	char *delim="-: ";
	char *p;
	printf("%s ",strtok(s,delim));
	while((p=strtok(NULL,delim))) printf("%s ",p);
	printf("\n");
}
