
#include <string.h>

int main()
{
	char dest[30] = "string(a)";
	char src[30] = "string\0string";
	int i;
//拷贝字符串（strcpy）
	strcpy(dest,src);	
		printf("strcpy() :");
	for(i=0;i<30;i++)
		printf("%c",dest[i]);
 
	putchar(10);
//比较内存内容(memcpy)
	memmove(dest,src, 30);//dest指针放在前
		printf("memmove():");
	for(i=0;i<30;i++)
		printf("%c",dest[i]);

	putchar(10);
}
