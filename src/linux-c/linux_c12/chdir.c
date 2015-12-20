#include <unistd.h>
	/*改变当前的工作(目录)*/
int main()
{
	chdir("/tmp");
	printf("current working directory: %s\n",
			getcwd(NULL,NULL));
}
