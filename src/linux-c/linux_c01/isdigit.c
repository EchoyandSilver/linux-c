#include <ctype.h>
//测试字符是否为阿拉伯数字
int main()
{
	char str[] = " 123c@#FDsP[e?";	
	int i;
	for( i=0 ; str[i] != 0; i++ )
		if(isdigit(str[i]))
			printf("%c is an digit  character\n",str[i]);

}

