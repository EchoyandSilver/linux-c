#include <stdio.h>
#define set_s (s,y) {strcoy(s[x].name,y),s[x].size=strlen(y);}
#define nmemb 3

struct test
{
	char name[20];
	int size;
}s[nmemb];
	
	//将数据写至文件流
int main()
{
	FILE *stream;
	set_s(0,"Linux!");
	set_s(1,"FreeBSD!");
	set_s(2,"Windows2000.");
	stream=fopen("file","w");
	fwrite(s,sizeof(struct test),nmemb,stream);	 	
	fclose(stream);
}

