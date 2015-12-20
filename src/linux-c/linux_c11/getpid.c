#include <unistd.h>
#include <stdio.h>

int main()
{
	/* 取得进程识别码 ，每一次执行结果都不一定相同*/
	if(vfork() == 0)
	{
		printf("pid = %d\n",getpid());
	}else{
		printf("ppid = %d\n",getppid());	/*取得父进程的识别码*/
	}
}
