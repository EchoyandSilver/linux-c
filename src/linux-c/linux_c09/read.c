#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	int fd;
	char buf[32] = {0};
	ssize_t bytes;

	fd = open("file",O_RDWR);
	if(fd < 0)
	{
		perror("fail to create file");
		return -1;
	}
		//由已打开的文件读取数据
	bytes = read(fd, buf,sizeof(buf));
	printf("bytes = %d\n",bytes);
	printf("\n");

	close(fd);
	return 0;
}
