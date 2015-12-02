#include <unistd.h>

int main()
{
	char *argv[] = {"ls","-al","/etc/passwd",(char *)0};
	execvp("ls",argv);
}
