#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

	//将数据写入已打开的文件内
int main()
{
	int fd;

	fd = open("file",O_RDWR|O_CREAT|O_TRUNC,0666);
	if(fd < 0)
	{
		perror("fail to create file");
		return -1;
	}
	write(fd,"helloworld",5);
	close(fd);
	return 0;
}
