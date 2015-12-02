#include <unistd.h>

int main()
{
	//从PATH环境变量中查找文件并执行
	execlp("ls","ls","-al","/etc/passwd",(char *)0);
}
