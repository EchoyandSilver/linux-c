#include <unistd.h>

int mian()
{
	//改变根目录
	chroot("/tmp");
	//改变当前工作(目录)
	chdir("/");
}
