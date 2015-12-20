#include <unistd.h>
#include <stdio.h>

   //判断是否具有存取文件的权限
int main ()
{
	if(access("/etc/passwd",R_OK) == 0)
	{
		//是否具有可读权限
		printf("/etc/passwd can be read");
	}
}
