#include <ctype.h>

int main()
{
	char c;
	c = 'a';
	if(iscntrl(c)){
		printf("c is iscntrl");
	}else{
		printf("c is not iscntrl");
	}
		putchar(10);
	return 0;
}
