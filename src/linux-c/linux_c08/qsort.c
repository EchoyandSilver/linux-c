#include <stdlib.h>
#define  nmemb 7

int compar(const void *a,const void *b)
{
	int *aa = (int *)a,**bb = (int *)b;
	if(*aa > *bb)	return 1;
	if(*aa == *bb)	return 0;
	if(*aa < *bb)	return -1;
}
	
//利用快速排序法排列数组
int main()
{
	int base[nmemb] = {3, 102, 5, -2, 98, 52, 18};
	int i;
	for(i=0;i < nmemb;i++){
		printf("%d ", base[i]);
	}
	printf("\n");
	qsort(base,nmemb,sizeof(int),compar);
	for(i=0;i < nmemb;i++){
		printf("%d ",base[i]);
	}
	printf("\n");
}
