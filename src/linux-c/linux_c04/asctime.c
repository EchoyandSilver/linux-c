#include <time.h>

int main()
{
	//将时间和日期以字符串的格式表示
	time_t timep;
	time(&timep);
	printf("%s\n",asctime(gmtime(&timep)));
}

