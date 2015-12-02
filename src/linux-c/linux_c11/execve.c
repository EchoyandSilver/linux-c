#include <unistd.h>

int main()
{	/*执行文件*/
	char *argv[] = {"ls","-al","/etc/passwd",(char *)0};
	char *envp[] = {"PATH=/bin",0};
	/* 第一个字符串代表文件路径，
	 第二个参数系利用数组指针来传递给执行文件,
	 第三个参数指传递给执行文件的新环境变量数组 */
	execve("/bin/ls",argv,envp);		
}
