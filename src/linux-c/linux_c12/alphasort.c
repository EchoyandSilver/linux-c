#include <dirent.h>
	/* 读取/目录下所有的目录结构并依字母顺序排列 */
int main()
{
	struct dirent **namelist;
	int i,total;
	/* 依字母顺序排序目录结构 */
	total = scandir("/",&namelist,0,alphasort);
	if(total < 0)
		perror("scandir");
	else
	{
		for(i = 0;i< total;i++){
			printf("%s\n",namelist[i]->d_name);
		}
			printf("total = %d\n",total);
	}
}
