#include <stdio.h>

int main()
{
	//打开文件
	FILE * fp;
	fp = fopen("file","a+");
	if(fp == NULL) 
		return;
	printf("file is open.");
	printf("\n");	
	fclose(fp);
}
