
#include <strings.h>
int main()
{
	//采用目前区域的字符排列次序来比较字符串
	char *a = "aBcDeF";
	char *b = "AbCdEf";
	char *c = "abcdef";
	char *d = "aBcDeF";
	printf("strcoll(a,b):%d\n",strcoll(a,b));
	printf("strcoll(a,c):%d\n",strcoll(a,c));
	printf("strcoll(a,d):%d\n",strcoll(a,d));
}
