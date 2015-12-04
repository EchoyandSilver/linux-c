#include <stdlib.h>

void my_exit(int status,void *arg)
{
	printf("before exit()!\n");
	printf("exit (%d)\n",status);
	printf("arg = %s\n",(char *)arg);
}

int main()
{
	char *str = "test";
	on_exit(my_exit,(void *)str);	//设置程序正常结束前调用的函数
	exit(1234);
}
