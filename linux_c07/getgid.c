#include <unistd.h>
#include <sys/types.h>

int main()
{
	//取得真实的组识别码
	printf("gid is %d \n",getpid());
}
