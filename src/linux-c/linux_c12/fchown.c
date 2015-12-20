#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
	
/*改变文件的所有者*/
int main()
{
	int fd;
	fd = open("/etc/passwd",O_RDONLY);
	chown(fd,0,0);
	close(fd);
}
