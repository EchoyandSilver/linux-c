#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
	/*改变当前的工作目录*/
int main()
{
	int fd;
	fd = open("/tmp",O_RDONLY);
	fchdir(fd);
	printf("current working directory: %s\n",getcwd(NULL,NULL));
}
