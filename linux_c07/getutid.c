#include <utmp.h>

int main()
{
	//从utmp文件中查找特定的记录
	struct utmp ut,*u;
	ut.ut_type=RUN_LVL;	 //记录系统run-level的改变
	while((u = getutid(&ut)))
	printf("%d %s %s %s\n",u->ut_type,u->ut_user,u->ut_line,u->ut_host);
}
