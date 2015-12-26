#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fd;
	char *file = "/dev/tty";
	fd = open(file,O_RDONLY);
	printf("%s",file);
	if(isatty(fd)){
		printf("is a tty.\n");
		printf("ttyname = %s\n",ttyname(fd));
	}
	else printf("is not a tty\n");
	close(fd);
}
