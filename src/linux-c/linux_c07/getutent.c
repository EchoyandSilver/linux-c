#include <utmp.h>

int main()
{
	//从utmp文件中取得帐号登录数据
	struct utmp *u;
	while((u = getutent()) != 0)
	{
		if(u->ut_type == BOOT_TIME)  //记录系统开机时间
		{
			printf("%d %s %s %s \n",u->ut_type,u->ut_user,u->ut_line,u->ut_host);
		}
		endutent();
	}
}
