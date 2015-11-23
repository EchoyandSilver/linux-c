#include <stdlib.h>
#include <time.h>

int main()
{
	//设置随机数种子
	int i,j;
	srand((int)time(0));
	for(i=0;i<10;i++){
		j = 1+(10.0*rand())/(RAND_MAX+1.0);
		printf("%d ",j);
	}
	printf("\n");
}
