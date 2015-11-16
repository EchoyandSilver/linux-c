#include <grp.h>
#include <sys/types.h>

int main()
{
	//从组文件中取得指定组的数据
	struct group * data;
	int i = 0;
	data = getgrnam("adm");
	printf("%s:%s:%d:",data->gr_name,data->gr_passwd,data->gr_gid);
	while(data->gr_mem[i])  printf("%s",data->gr_mem[i++]);
	printf("\n");
}
