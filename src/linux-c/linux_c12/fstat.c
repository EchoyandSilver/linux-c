#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
	
	/*由文件描述词取得文件状态*/
int main()
{
	struct stat buf;
	int fd;
	fd = open("/etc/passwd",O_RDONLY);
	fstat(fd,&buf);
	printf("/etc/passwd file size = %d\n",buf.st_size);
}
