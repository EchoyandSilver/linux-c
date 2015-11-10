#include <stdlib.h>

int main()
{
	//将字符串转换成整形数
	//将字符串a与字符串b转换成数字后相加
	char a[] = "-100";
	char b[] = "456";
	int c;
	c = atoi(a) + atoi(b);
	printf("c=%d\n",c);
}
