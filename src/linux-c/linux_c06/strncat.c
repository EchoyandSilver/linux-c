#include <string.h>

int main()
{
	//连接两字符串（将源字符串的前n个字符拼接到目的字符串后）
	char a[30]="string(1)";
	char b[]="string(2)";
	printf("before strncat():%s\n",a);
	printf("after strncat():%s\n",strncat(a,b,7));
}
