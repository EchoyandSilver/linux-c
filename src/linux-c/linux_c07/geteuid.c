#include <unistd.h>
#include <sys/types.h>

int main()
{
	//取得有效的用户识别码
	printf("euid : %d \n",geteuid());
}
