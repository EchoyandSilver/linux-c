#include <string.h>

int main()
{
	//忽略大小写比较字符串
	char *a = "aBcDeF";
	char *b = "AcCdEf";
	if(!strcasecmp(a,b))
	printf(" %s = %s\n",a,b);
}
