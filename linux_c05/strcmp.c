
#include <strings.h>
int main()
{
	//比较字符串
	char *a = "aBcDeF";
	char *b = "AbCdEf";
	char *c = "abcdef";
	char *d = "aBcDeF";
	printf("strcmp(a,b):%d\n",strcmp(a,b));
	printf("strcmp(a,c):%d\n",strcmp(a,c));
	printf("strcmp(a,d):%d\n",strcmp(a,d));
}
