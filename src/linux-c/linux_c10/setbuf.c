#include <stdio.h>

char outbuf[50];
	//设置文件流的缓冲区
int main()
{ 
	//将outbuf与stdout输出流相连接
	setbuf(stdout,outbuf);
	//向stdout放入一些字符串
	puts("This is a test of buffered output");
	puts("This output will go into outbuf");
	puts("and won't appear until the buffer");
	// ...
	//以下是outbuf中的内容
	puts(outbuf);
	//刷新流
	fflush(stdout);

	return 0;
}
