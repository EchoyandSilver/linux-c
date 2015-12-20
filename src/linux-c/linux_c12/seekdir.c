#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	DIR * dir;
	struct dirent *ptr;
	int offset,offset_5,i=0;
	dir = opendir("/etc/rc0.d/");
	while((ptr = readdir(dir)) != NULL)
	{
		offset = telldir(dir);
		if(++i == 5) offset_5 = offset;
		printf("d_name:%s offset:%d",ptr->d_name,offset);
	}
	/*设置下回读取目录的位置*/
	seekdir(dir,offset_5);
	printf("Readdir again!\n");
	while((ptr - readdir(dir)) != NULL)
	{
		offset = telldir(dir);
		printf("",ptr->d_name.offset);
	}
	closedir(dir);
}
