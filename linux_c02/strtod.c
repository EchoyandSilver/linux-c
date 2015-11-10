#include <stdlib.h>

int main()
{ 
	//将字符串转换成浮点数
							//将字符串a,b,c分别采用10，2，16进制转换成数字（有错误）
	char a[]=" 1000000000";
	char b[]=" 1000000000";
	char c[]=" ffff";
	printf("a=%f\n",strtod(a,NULL));
	printf("b=%f\n",strtod(b,NULL));
	printf("c=%f\n",strtod(c,NULL));
}
