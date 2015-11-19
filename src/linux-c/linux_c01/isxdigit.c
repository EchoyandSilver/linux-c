#include <stdio.h>

int main()
{
	//测试找出字符串str中十六进制数字字符
	char str[] = "123c@#FDsP[e?";
	int i;
	for(i = 0; str[i] != 0; i++ )
		if(isxdigit(str[i]))
			printf("%c is a hexadecimal digits \n", str[i]);

}
