#include "Test.h"

int main(void)
{
/*
	Test t(10);

	t = 20;

	Test t2;

*/
	Test t = 10; 	// Test t = 10  <==> Test t(10);
	
	t = 20;	

	Test t2;
	t = t2;		//t.operator=(t2);

	return 0;
}
