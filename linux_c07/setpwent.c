#include <pwd.h>
#include <sys/types.h>

int main()
{
	//从头读取密码文件的帐号数据
	struct passwd *user;
	int i;
	for(i=0;i<4;i++)
		user=getpwent();
	printf("%s:%d:%s:%s:%s\n",user->pw_name,user->pw_uid,user->pw_gecos,
				user->pw_dir,user->pw_shell);
	setpwent();
	user = getpwent();
	printf("%s:%d:%s:%s:%s\n",user->pw_name,user->pw_uid,user->pw_gecos,
			user->pw_dir,user->pw_shell);
	endpwent();
}
