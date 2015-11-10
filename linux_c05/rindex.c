#include <string.h>

int main()
{
	//查找字符串中最后一个出现的指定字符
	char *s="01234567890123456789";
	char *p;
	p = rindex(s,'5');
	printf("%s\n",p);
}
