#include <pwd.h>
#include <sys/types.h>

int main()
{
	//从密码文件中取得指定帐号的数据
	struct passwd *user;
	user = getpwnam("root");	//取得帐号的识别码和根目录
	printf("name:%s\n",user->pw_name);
	printf("uid:%d\n",user->pw_uid);
	printf("home:%s\n",user->pw_dir);
}
