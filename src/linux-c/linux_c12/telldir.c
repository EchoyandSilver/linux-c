#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

int main()
{
	DIR *dir;
	struct dirent *ptr;
	int offset;
	dir = opendir("/etc/rc0.d");
	while((ptr = readdir(dir)) != NULL)
	{	
		/*取得目录流的读取位置*/
		offset = telldir(dir);
		printf("d_name : %s offset : %d\n",ptr->d_name,offset);
	}
	closedir(dir);
}
