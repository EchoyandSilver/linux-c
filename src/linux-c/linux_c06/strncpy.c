#include <string.h>

int main()
{
	//拷贝字符串（拷贝源字符串的前n个字符到目的字符串）
	char a[30]="string(1)";
	char b[]="string(2)";
	printf("before strncpy():%s\n",a);
	printf("after strncpy():%s\n",strncpy(a,b,6));
}
