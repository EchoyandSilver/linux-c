#include <unistd.h>
#include <sys/types.h>

int main()
{
	//取得组代码
	gid_t list[500];
	int x,i;
	x = getgroups(0,list);
	getgroups(x,list);
	for(i=0;i<x;i++)
		printf("%d:%d\n",i,list[i]);
}
