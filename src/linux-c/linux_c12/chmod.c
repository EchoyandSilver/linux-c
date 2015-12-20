#include <sys/types.h>
#include <sys/stat.h>
	
	/*改变文件的权限*/
int main()
{
	chmod("/etc/passwd",S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
}
