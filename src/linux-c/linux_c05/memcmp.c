
#include <strings.h>
int main()
{
	//比较内存内容
	char *a = "aBcDeF";
	char *b = "AbCdEf";
	char *c = "abcdef";
	char *d = "aBcDeF";
	printf("memcmp(a,b):%d\n",bcmp((void*)a,(void*)b,6));
	printf("memcmp(a,c):%d\n",bcmp((void*)a,(void*)c,6));
	printf("memcmp(a,d):%d\n",bcmp((void*)a,(void*)d,6));
}
