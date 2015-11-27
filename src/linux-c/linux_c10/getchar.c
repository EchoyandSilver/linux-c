#include <stdio.h>

int main()
{
	//由标准输入设备内读进一个字符
	FILE *fp;
	int c,i;
	for(i=0;i<5;i++)
	{
		c = getchar();
		putchar(c);
	}
}
