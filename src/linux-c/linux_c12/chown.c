#include <sys/types.h>
#include <unistd.h>

	/*改变文件的所有者*/
int main()
{	
	chown("/etc/passwd",0,0);
}

