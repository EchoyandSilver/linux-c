#include <grp.h>
#include <sys/types.h>

int main()
{
	//从组文件中取得帐号的数据
	struct group *data;
	int i;
	while((data = getgrent()) != 0)
	{
		i = 0;
		printf("%s:%s:%d:",data->gr_name,data->gr_passwd,data->gr_gid);
		while(data->gr_mem[i])
			printf("%s",data->gr_mem[i++]);
		printf("\n");
	}
	//关闭组文件
	endgrent();
}
