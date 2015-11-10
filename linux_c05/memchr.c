#include <string.h>

int main()
{
	//在某一内存范围中查找一特定字符
	char *s = "01234567890123456789";
	char *p;
	p = memchr(s,' 5',10);
	printf("%s\n",p);
}
