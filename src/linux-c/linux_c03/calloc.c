#include <stdlib.h>

struct test
{
	int a[10];
	char b[20];
};

int main()
{	//动态配置10个struct test空间
	struct test *ptr = calloc(sizeof(struct test),10);
	//配置1k的内存
	void *p = malloc(1024);
	//取得内存分页大小
	printf("page size = %d\n",getpagesize());
	//释放内存
	free(NULL);
}
