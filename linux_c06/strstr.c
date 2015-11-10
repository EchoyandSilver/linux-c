#include <string.h>

int main()
{
	//在一字符串中找出指定的字符串
	char *s1="01234567890123456789";
	char *s2;
	s2=strstr(s1,"901");
	printf("%s\n",s2);
}
