#include <unistd.h>
	
	/*建立文件的连接*/
int main()
{
	/*建立/etc/passwd的硬连接为pass*/
	link("/etc/passwd","pass");
}
