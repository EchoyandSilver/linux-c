#include <string.h>

int main()
{
	//忽略大小写比较字符串
	char *a = "aBcDeF";
	char *b = "AbCdEf";
	printf("strcasecmp():%d\n",strcasecmp(a,b));
}
