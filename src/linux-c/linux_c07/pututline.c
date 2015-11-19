#include <utmp.h>

int main()
{
	//将utmp记录写入文件
	struct utmp ut;
	ut.ut_type = USER_PROCESS;
	ut.ut_pid = getpid();
	strcpy(ut.ut_user,"kids");
	strcpy(ut.ut_line,"pts/1");
	strcpy(ut.ut_host,"www.gun.org");
	pututline(&ut);
}
