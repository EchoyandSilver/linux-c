#include <grp.h>
#include <sys/types.h>

int main()
{
	//从头读取组文件中的组数据
	struct group *data;
	int i;
	while((data = setgrent()) != 0)
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
