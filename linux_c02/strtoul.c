#include <stdlib.h>

int main()
{ 
	//将字符串转换成长整形数
	//将字符串a,b,c分别采用10，2，16进制转换成数字
	char a[]=" 1000000000";
	char b[]=" 1000000000";
	char c[]=" ffff";
	printf("a=%d\n",strtoul(a,NULL,10));
	printf("b=%d\n",strtoul(b,NULL,2));
	printf("c=%d\n",strtoul(c,NULL,16));
}
