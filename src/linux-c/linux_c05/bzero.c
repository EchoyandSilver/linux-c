#include <string.h>

int main()
{
	//将一段内存内容全清为0
	char s[10]="123456789";
	bzero(s,sizeof(s));
	s[10]='\0';
	printf("%s\n",s);
}
