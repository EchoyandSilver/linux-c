#include <string.h>

int main()
{
	//将一段内存空间填入某值
	char s[10];
	memset(s,'A',sizeof(s));
	s[10]='\0';
	printf("%s\n",s);
}
