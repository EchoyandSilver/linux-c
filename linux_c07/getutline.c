#include <utmp.h>

int main()
{
	//在utmp文件中查找特定的记录
	struct utmp ut,*u;
	strcpy(ut.ut_line,"pts/1");
	while(( u = getutline(&ut)))	//登录帐号的远程主机名
		printf("%d %s %s %s \n",u->ut_type,u->ut_user,u->ut_line,u->ut_host);
}
