#include <stdlib.h>

int main()
{
	//建立唯一的临时文件
	int fd;
	char template[] = "template-XXXXXX";
	fd = mkstemp(template);
	printf("template = %s \n",template);
	close(fd);
}
