#include <unistd.h>
#include <sys/types.h>

int main()
{
	//取得真实的用户识别码
	printf("uid is : %d\n",getuid());
}
