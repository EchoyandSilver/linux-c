#include <string.h>

int main()
{
	//拷贝内存内容
	char a[]="string[a]";
	char b[]="string(b)";
	memccpy(a,b,'b',sizeof(b));
	printf("memccpy():%s\n",a);
	putchar(10);
}
