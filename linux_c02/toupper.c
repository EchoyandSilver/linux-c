#include <stdio.h>

int main()
{
	//将小写字母转换成大写字母
	//将s内的小字母转换成大写字母
	char s[]="aBcDeFgH12345;!#$";
	int i;
	printf("before toupper : %s\n",s);
	for(i=0;i<sizeof(s);i++)
		s[i]=toupper(s[i]);
	printf("after  toupper ： %s\n",s);

}
