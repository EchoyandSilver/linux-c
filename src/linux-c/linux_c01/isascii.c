#include <ctype.h>

int main()
{
	//测试字符是否为ASCII码字符
	int i;
	for(i = 125; i < 130; i++)
	if(isascii(i))
		printf("%d is an ascii character:%c\n", i, i);
	else
		printf("%d is not an ascii character\n", i, i);

}
