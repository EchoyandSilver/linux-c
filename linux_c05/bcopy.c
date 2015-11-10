#include <string.h>

int main()
{
	char dest[30] = "string(a)";
	char src[30] = "string\0string";
	int i;
//拷贝内存内容（bcopy）
	bcopy(src,dest,30);//src指针放在前
		printf("bcopy() :");
	for(i=0;i<30;i++)
		printf("%c",dest[i]);
 
	putchar(10);
//比较内存内容(memcpy)
	memcpy(dest,src, 30);
		printf("memcpy():");//dest指针放在前
	for(i=0;i<30;i++)
		printf("%c",dest[i]);

	putchar(10);
}
