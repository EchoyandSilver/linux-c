#include <ctype.h>

int main()
{
	//将字符串str[]中内涵的空格符找出，并显示空格字符的ascii码值
	char str[] = "123c @# FD\tsP[e?\n";
	int i;
	for(i = 0;str[i] != 0; i++)
		if(isspace(str[i]))
			printf("str[%d] is white-space character:%d\n",i,str[i]);
 
}
