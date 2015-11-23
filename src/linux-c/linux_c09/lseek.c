#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

	//移动文件的读写位置
int main()
{
	off_t off;
	int fd;
	
	fd = open("file",O_RDWR);	//打开文件描述符
	if(fd < 0)
	{
		perror("fail to creat file");
		return -1;
	}

	off = lseek(fd,0,SEEK_END); 	//从文件末尾位置开始读写
	printf("off = %ld\n",off);

	close(fd);	//关闭文件描述符
	return 0;
}
