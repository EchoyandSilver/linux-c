#include <stdio.h>

int main()
{
	//返回文件流所使用的文件描述符
	FILE * fp;
	int fd;
	fp = fopen("file","r");
	fd = fileno(fp);
	printf("fd = %d\n",fd);
	close(fd);
}
