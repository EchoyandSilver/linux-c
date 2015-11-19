#include <grp.h>
#include <stdio.h>
#include <sys/types.h>

int main()
{
	//从指定文件来读取组格式
	struct group *data;
	FILE *stream;
	int i;
	stream = fopen("/etc/group","r");
	while((data = fgetgrent(stream)) != 0)
	{
		int i;
		printf("%s:%s:%d:",data->gr_name,data->gr_passwd,data->gr_gid);
		while(data->gr_mem[i]) printf("%s,",data->gr_mem[i++]);
		printf("\n");
	}
	fclose(stream);
}
