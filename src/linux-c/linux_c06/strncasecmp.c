#include <string.h>

int main()
{
	//忽略大小写比较字符串
	char *a="aBcDeF";
	char *b="AbCdEf";
	if(!strncasecmp(a,b,6))
	printf("%s=%s\n",a,b);
}
