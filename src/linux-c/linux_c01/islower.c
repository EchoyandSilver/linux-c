#include <ctype.h>
//测试字符是否为小写字母
int main()
{
	char str[] = " 123c@#FDsP[e?";	
	int i;
	for(i = 0; str[i] != 0; i++)
		if(islower(str[i]))
			printf("%c is a lower-case character\n",str[i]);

}

