#include <stdio.h>

int main()
{
	//产生唯一的临时文件名
	char template[] = "template-XXXXXX";
	mktemp(template);
	printf("temp=%s\n",template);
}
