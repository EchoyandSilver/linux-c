#include <sys/stat.h>
#include <unistd.h>
	
	/*取得文件的状态*/
int mian()
{
	struct stat buf;
	stat("/etc/passwd",&buf);
	printf("/etc/passwd file size = %d\n",buf.st_size);
}
