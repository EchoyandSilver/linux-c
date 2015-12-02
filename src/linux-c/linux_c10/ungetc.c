#include <stdio.h>
#include <ctype.h>

void main()
{
	int ch;
	int result = 0;
	printf("Enter an integer:");
	/* Read in and convert number: */
	while(((ch = getchar())!= EOF)&&isdigit(ch))	
		result = result*10 + ch - '0';	/* use digit */
	if(ch != EOF)
		/*Put nondigit back*/
	ungetc(ch,stdin);	//将字符串写回到文件流中  
	printf("Number = %d\nNextcharacter in stream = '%c'",result,getchar());
}
