#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
	
	/*重设读取目录的位置为开头位置*/
int main()
{
	DIR *dir;
	struct dirent *ptr;
	dir = opendir("/etc/rc0.d");
	while((ptr = readdir(dir)) != NULL)
	{
		printf("d_name:%s\n",ptr->d_name);
	}
		rewinddir(dir);
		printf("readdir again!\n");
		while((ptr = readdir(dir)) != NULL)
		{
			printf("d_name:%s\n"ptr->d_name);
		}
		closedir(dir);
}
