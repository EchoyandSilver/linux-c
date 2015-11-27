#include <stdio.h>

int main()
{
	//将一字符写入文件流中
	FILE * fp;
	char a[7] = "absdefg";
	int i;
	fp = fopen("file","w");
	for(i=0;i< 7;i++)
		fputc(a[i],fp);
	fclose(fp);
}
