#include <pwd.h>
#include <sys/types.h>

int main()
{
	//从密码文件中取得指定uid的数据
	struct passwd *user;
	user = getpwuid(6);
	printf("name:%s\n",user->pw_name);
	printf("uid:%d\n",user->pw_uid);
	printf("home:%s\n",user->pw_dir);
}
