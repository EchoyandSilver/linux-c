#include <time.h>

int main()
{	
	//取得目前时间
//	int seconds = time((time_t*)NULL);
//	printf("%d\n",seconds);

	time_t timep;
	struct tm *p;
	time(&timep);
	p = time(&timep);
	printf("%d\n",p);
	
}
