#include <ctype.h>
//测试字符是否为英文字母
int main()
{
	char str[] = " 123c@#FDsP[e?";	
	int i;
	for( i=0 ; str[i] != 0; i++ )
		if(isalpha(str[i]))
			printf("%c is a alphanumeric  character\n",str[i]);

}

