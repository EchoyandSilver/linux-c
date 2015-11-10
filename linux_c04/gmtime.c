#include <time.h>

int main()
{
	// 取得目前时间和日期
	char *wday[]={"Sun","Sat","Mon","Tue","Wed","Thu","Fir"};
	time_t timep;
	struct tm *p;
	time(&timep);
	p = gmtime(&timep);
	printf("%d %d %d ",(1900+p->tm_year),(1+p->tm_mon),(p->tm_mday));
	printf("%s %d:%d:%d\n",wday[p->tm_wday],p->tm_hour,p->tm_min,p->tm_sec);
}
