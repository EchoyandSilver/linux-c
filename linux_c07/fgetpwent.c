#include <pwd.h>
#include <sys/types.h>

int main()
{
	//从指定文件来读取密码格式
	struct passwd *user;
	FILE *stream;
	stream = fopen("/etc/passwd","r");
	while((user = fgetpwent(stream)) != 0)
		printf("%s:%d:%s:%s:%s\n",user->pw_name,user->pw_uid,user->
				pw_gecos,user->pw_dir,user->pw_shell);
}
