#include <stdio.h>

int main()
{
	FILE *fp;
	fp = fopen("file","r");		// 打开文件
	//参数stream为已打开的文件指针，freopen()会将原stream所打开的文件流关闭，
	//然后打开参数path文件
	fp = freopen("file","r",fp);
	fclose(fp);
}
