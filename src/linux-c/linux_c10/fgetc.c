#include <stdio.h>

//由文件读取一个字符
int main()
{
	
	FILE * fp;
	int c;
	fp = fopen("file","r");
	while((c = fgetc(fp)) != EOF)	//一个字符一个子符打印文件内容
	{
		printf("%c ",c);
	}
	fclose(fp);
}
