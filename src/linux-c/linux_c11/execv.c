#include <unistd.h>

int main()
{
	char *argv[]={"ls","-al","/etc/passwd",(char *)0};
	/*执行文件，execv（）只需要两个参数，
	第二个参数利用数组指针来传递给执行文件 */
	execv("/bin/ls",argv);
}
