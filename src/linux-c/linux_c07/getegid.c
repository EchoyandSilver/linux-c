#include <unistd.h>
#include <sys/types.h>

int main()
{
	//取得有效的组识别码
	printf("egid: %d\n",getegid());
}
