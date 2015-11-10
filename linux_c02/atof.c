#include <stdlib.h>

int main()
{
	//将字符串装换成浮点型数
	//将字符串a与字符串b转换成数字后相加
	char *a="-100.23";
	char *b="200e-2";
	float c;
	c = atof(a)+atof(b);
	printf("c=%.2f\n",c);
}
