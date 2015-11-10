#include <strings.h>
int main()
{
	//比较内存内容
	char *a = "aBcDeF";
	char *b = "AbCdEf";
	char *c = "abcdef";
	char *d = "aBcDeF";
	printf("bcmp(a,b):%d\n",bcmp((void*)a,(void*)b,6));
	printf("bcmp(a,c):%d\n",bcmp((void*)a,(void*)c,6));
	printf("bcmp(a,d):%d\n",bcmp((void*)a,(void*)d,6));
}
