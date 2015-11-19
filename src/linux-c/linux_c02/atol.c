#include <stdlib.h>

int main()
{
	//将字符串转换成长整形数
	//将字符串a与字符串b转换成数字后相加 
	char a[]="1000000000";
	char b[]=" 234567890";
	long c;
	c=atol(a)+atol(b);
	printf("c=%d\n",c);
}
