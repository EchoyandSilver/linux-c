#include <string.h>

int main()
{
	//拷贝字符串
	char a[]="string(1)";
	char b[]="string(2)";
	printf("before strcpy():%s\n",a);
	printf("after strcpy():%s\n",strcpy(a,b));

}
