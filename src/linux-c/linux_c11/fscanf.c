#include <stdio.h>
int main()
{
	int i;
	unsigned int j;
	char s[5];
	fscanf(stdin,"%d %x %5[a-z] %*s",&i,&j,s,&s);	// 格式化字符串输入
	printf("%d %d %s \n",i,j,s);
}
