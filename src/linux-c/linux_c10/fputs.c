#include <stdio.h>

int main()
{
	//向文件内写入一字符串
	char s[7];
	int fd;
	fputs(fgets(s,7,stdin),stdout);
	close(fd);
	fprintf("\n");
}
