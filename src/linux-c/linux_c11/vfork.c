#include <unistd.h>
#include <stdio.h>

int main()
{
	//建立一个新的进程
	if(vfork() == 0)
	{
		printf("This is the child process\n");
	}else{
		printf("This is the parent process\n");
	}
}
