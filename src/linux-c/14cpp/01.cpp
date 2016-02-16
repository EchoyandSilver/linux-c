#include "Test.h"

int main(void)
{
	Test t(10);
	//Test t2(t);
	Test t2 = t;	//<==>Test t2(t)

	return 0;
}
