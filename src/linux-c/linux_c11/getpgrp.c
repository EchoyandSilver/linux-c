#include <unistd.h>

int main()
{
	/*用来取得目前进程所属的组识别码，
	此函数相当与调用getpgid(0)*/
	printf("my gid = %d\n",getpgrp());
}
