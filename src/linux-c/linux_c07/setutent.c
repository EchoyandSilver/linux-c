#include <utmp.h>

int main()
{
	//从utmp文件中取得帐号登录数据
	struct utmp *u;
	u = getutent();
		if(u->ut_type == BOOT_TIME)  //记录系统开机时间
		{
			printf("%d %s %s %s \n",u->ut_type,u->ut_user,u->ut_line,u->ut_host);
		}
	setutent();
	u = getutent();		//从头读取utmp文件中的登录数据
		if(u->ut_type == BOOT_TIME)  //记录系统开机时间
		{
			printf("%d %s %s %s \n",u->ut_type,u->ut_user,u->ut_line,u->ut_host);
		}
	endutent();	//关闭utmp文件
}
