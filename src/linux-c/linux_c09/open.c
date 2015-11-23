#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

	
int main()
{
	int fd, size;
	char s[] = "Linux Programmer!\n", buffer[80];
	fd = open("file",O_WRONLY|O_CREAT);	//打开只写文件
	write(fd,s,sizeof(s));	//对file文件进行写操作
	close(fd);	//关闭文件
	fd = open("file",O_RDONLY);	//打开只读文件
	size = read(fd,buffer,sizeof(buffer));	//对file文件进行读操作
	close(fd);	//关闭文件
	printf("%s \n",buffer);
	printf("%d \n",size);
}

