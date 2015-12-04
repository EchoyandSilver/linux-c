#include <stdio.h>

int main()
{
	char * a = "This is string A!";
	char buf[80];
	sprintf(buf,">> %s <<",a);	//格式化字符串复制
	printf("%s",buf);
}
