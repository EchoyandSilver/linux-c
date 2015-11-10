#include <time.h>

int main()
{
	//将时间结构数据转换成经过的秒数
	time_t timep;
	struct tm *p;
	time(&timep);
	printf("time():%d\n",timep);
	p = localtime(&timep);
	timep = mktime(p);
	printf("time()->localtime()->mktime() :%d\n",timep);
}
