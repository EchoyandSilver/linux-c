#include <stdlib.h>

void my_exit()
{
	printf("before exit() !\n");
}

int main()
{
	atexit(my_exit);	//设置程序正常结束前调用的函数
	exit(0);
}
