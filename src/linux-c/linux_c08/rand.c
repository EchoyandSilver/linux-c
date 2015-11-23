#include <stdlib.h>

int main()
{
	//产生随机数
	int i,j;
	for(i=0;i<10;i++)
	{
		j=1+(int)(10.0*rand())/(RAND_MAX+1.0);
		printf("%d ", j);
	}
	printf("\n");
}
