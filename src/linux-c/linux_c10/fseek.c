#include <stdio.h>

int main()
{
	FILE *stream;
	long offset;
	fpos_t  pos;
	stream=fopen("file","r");
	fseek(stream,5,SEEK_SET);	//移动文件流的读写位置
	printf("offset=%ld\n",ftell(stream));	//取得文件流的读取位置
	rewind(stream);		//重设文件流的读写位置为文件开头
	fgetpos(stream,&pos);	// 文件位置的获得
	fsetpos(stream,&pos);	//文件位置的设置
	printf("offset = %ld\n",ftell(stream));	//取得文件流的读取位置
	fclose(stream);
}
