#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
	
	/*读取目录*/
int main()
{
	DIR * dir;
	struct dirent *ptr;
	int i;
	dir = opendir("/etc/rc.d");
	while(ptr = readdir(dir) != NULL)
	{
		printf("d_name: %s\n",ptr->d_name);
	}
	closedir(dir);
}
