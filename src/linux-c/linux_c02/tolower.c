#include <stdlib.h>

int main()
{
	//将大写字母转换成小写字母
	//将s字符串内的大写字母转换成小写字母
	char s[]=" aBcDeFgH12345;！#$";
	int i;
	printf("before tolower() : %s\n",s);
	for(i=0;i<sizeof(s);i++)
		s[i]=tolower(s[i]);
		printf("after  tolower() : %s\n",s);
}

