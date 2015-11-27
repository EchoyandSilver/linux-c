#include <stdio.h>

	//由文件中读取一字符串
int main()
{
	char s[80];
	fputs(fgets(s,80,stdin),stdout);
}
