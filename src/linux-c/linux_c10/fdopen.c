#include <stdio.h>

int main()
{
	//将文件描述词转为文件指针
	FILE * fp = fdopen(0,"w+");
	fprintf(fp,"%s\n","hello world!");
	fclose(fp);
}

