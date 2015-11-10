#include <string.h>

int main()
{
	//返回字符串中连续不含指定字符串内容的字符数
	char *str="Linux was first developed for 386/486-basedpcs";
	printf("%d\n",strcspn(str," "));
	printf("%d\n",strcspn(str,"/-"));
	printf("%d\n",strcspn(str,"1234567890"));
}
