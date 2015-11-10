#include <ctype.h>

int main()
{
	//测试str字符串中哪些是可打印字符(不打印空格)：
	char str[] =  "a5 @;";
	int i;
	for( i = 0; str[i] != 0; i++)
		if(isgraph(str[i]))
			printf("str[%d] is printable character:%c\n", i, str[i]);

}
