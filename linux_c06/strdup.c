#include <string.h>

int main()
{
	//复制字符串
	char a[]=" strdup";
	char *b;
	b=strdup(a);
	printf("b[] =%s\n",b);
}
