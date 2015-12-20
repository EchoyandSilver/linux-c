#include <unistd.h>

	/*建立文件符号的连接*/
int main()
{
	symlink("/etc/passwd","pass");
}
