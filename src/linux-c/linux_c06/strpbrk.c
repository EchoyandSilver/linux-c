#include <string.h>

int main()
{
	//查找字符串中第一个出现的指定字符
	char *s="012345678901234567890";
	char *p;
	p=strpbrk(s,"a1 839");
	printf("%s\n",p);
	p=strpbrk(s,"4398");
	printf("%s\n",p);
}
