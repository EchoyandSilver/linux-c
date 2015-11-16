#include <utmp.h>

int main()
{
	//从头读取utmp文件中的登录数据
	struct utmp *u;
	int i;
	for(i=0;i<4;i++){
		u=getutent();
	printf("%d %s %s %s\n",u->ut_type,u->ut_user,u->ut_line,u->ut_host);
	}
	setutent();
	u = getutent();
	printf("%d %s %s %s\n",u->ut_type,u->ut_user,u->ut_line,u->ut_host);
	//关闭utmp文件
	endutent();
}
