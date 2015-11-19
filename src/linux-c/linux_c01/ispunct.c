#include <ctype.h>
//测试字符是否为标点符号或者特殊符号
int main()
{
	char str[] = " 123c@#FDsP[e?";	
	int i;
	for( i=0 ; str[i] != 0; i++ )
		if(ispunct(str[i]))
			printf("%c \n",str[i]);

}

