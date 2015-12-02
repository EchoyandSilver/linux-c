#include <stdio.h>

int main ()
{
	FILE *output;
	output = fopen("file.out","w");
	/* set up output stream for line buffering using space that
	 will be obtained through an indirect call to malloc*/
	setlinebuf(output);
	/* perform file I/O here*/
	fclose(output);
	return 0;
}
