#include <stdio.h>
#define nmemb 3

struct test
{
	char name[20];
	int size;
}s[nmemb];
	
int main()
{
	FILE *stream;
	int i;
	stream =fopen("file","r");
	fread(s,sizeof(s),nmemb,stream);	//从文件流读取数据
	fclose(stream);
	for(i=0;i < nmemb;i++)
	{
		printf("name[%d]=%s : size[%d]=%d\n",i,s[i].name,i,s[i].size);
	}
}

