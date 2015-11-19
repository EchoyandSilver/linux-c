#include <pwd.h>
#include <sys/types.h>

int main()
{
	//取得指定用户的密码文件数据
	char buffer[80];
	getpw(0,buffer);
	printf("%s\n",buffer);
}
