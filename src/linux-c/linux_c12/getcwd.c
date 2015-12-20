#include <unistd.h>
	
	/*取得当前的工作目录*/
int main()
{
	char buf[80];
	getcwd(buf,sizeof(buf));
	printf("current working directory : %s\n",buf);
}
