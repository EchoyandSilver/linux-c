#include <string.h>

int main()
{
	//连接两字符串
	char a[]="string(1)";
	char b[]="string(2)";
	printf("before strcat():%s\n",a);
	printf("after  strcat():%s\n",strcat(a,b));
}
