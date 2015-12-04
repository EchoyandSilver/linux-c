#include <stdio.h>
#include <stdarg.h>

FILE *fp;

int vfsf(char *fmt,...)
{
	va_list argptr;
	int cnt;
	va_start(argptr,fmt);
	/* 格式化字符串输入,vfscanf()会自参数stream的文件流中读取字符串，
	 * 再根据参数format字符串来转换并格式化数据，
	 * 注意va_list的用法*/
	cnt = vfscanf(fp,fmt,argptr);	
	va_end(argptr);
	return(cnt);
}

int main()
{
	int inumber = 30;
	float fnumber = 90.0;
	char string[4] = "abc";
	fp = tmpfile();
	if(fp == NULL)
	{
		perror("tmpfile() call");
		return -1;
	}
	fprintf(fp,"%d %f %s\n",inumber,fnumber,string);
	rewind(fp);
	vfsf("%d %f %s",&inumber,&fnumber,string);
	printf("%d %f %s\n",inumber,fnumber,string);
	fclose(fp);
	return 0;
}
