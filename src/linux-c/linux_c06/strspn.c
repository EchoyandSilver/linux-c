#include <string.h>

int main()
{
	//返回字符串中连续不含指定字符串内容的字符数
	char *s1="Linux was first developed for 386/486-basedPCs.";
	char *s2="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	printf("%d\n",strspn(s1,s2));
}
