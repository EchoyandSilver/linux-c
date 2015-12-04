#include <stdio.h>

int main()
{
	int i = 150;
	int j = -100;
	double k = 3.14159;
	fprintf(stdout,"%d %f %x \n",j, k, i);	//格式化输出数据至文件
	fprintf(stdout,"%2d %*d\n",i,2,i);
}
