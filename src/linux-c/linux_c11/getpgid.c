#include <unistd.h>
#include <stdio.h>

int main()
{
	/*取得pid指定进程所属的组识别码*/
	printf("init gid = %d\n",getpgid(1));
}
