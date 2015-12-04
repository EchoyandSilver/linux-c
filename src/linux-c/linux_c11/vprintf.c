#include <stdio.h>
#include <stdarg.h>

int my_printf(const char *format,...)
{
	va_list ap;
	int retval;
	va_start(ap,format);
	printf("my_printf():");
	retval = vprintf(format,ap);	//格式化输出数据
	va_end(ap);
	return retval;
}

int main()
{
	int i = 150, j = -100;
	double k = 3.14159;
	my_printf("%d %f %x\n",j,k,i);
	my_printf("%2d %*d\n",i,2,i);
}
