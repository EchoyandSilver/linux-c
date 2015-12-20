#include <stdio.h>

	/*更改文件的名称或位置*/
void main(int argc,char **argv)
{
	if(argc < 3)
	{
		printf("Usage:%s old_name new_name\n",argv[0]);
		return;
	}
	printf("%s = %s",argc[1],argv[2]);
	if(rename(argv[1],argv[2]) < 0)
	printf("error!\n");
	else
		printf("ok!\n");
}
