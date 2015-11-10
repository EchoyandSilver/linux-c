#include <sys/time.h>
#include <unistd.h>



int main()
{
	//取得目前的时间
	struct timeval tv;	//tv存放目前的时间
	struct timezone tz;	//tz存放当地时区的信息
	settimeofday(&tv,&tz);	
	printf("tv_sec :%d\n",tv.tv_sec);	//秒
	printf("tv_usec :%d\n",tv.tv_usec);	//微秒
	printf("tz_minuteswest :%d\n",tz.tz_minuteswest);	//和Greenwich时间差了多少分钟
	printf("tz_dsttime :%d\n",tz.tz_dsttime);	//日光节约时间的状态（各各国家）
}
