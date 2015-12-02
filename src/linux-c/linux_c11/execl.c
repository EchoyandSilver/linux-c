#include <unistd.h>

int main()
{
	//执行文件
	execl("/bin/ls","ls","-al","/etc/passwd",NULL);	// NULL == (char *)0
}
