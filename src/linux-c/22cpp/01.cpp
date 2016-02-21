#include "Complex.h"

int main(void)
{
	Complex c1(3, 5);
	Complex c2(4, 6);

	//c1.Add(c2);
	//c1.Display();

	Complex c3 = c1 + c2;	// <==>c1.operator(c2); or operator+(c1, c2);
	//Complex c3 = c1.operator + (c2);
	c1.Display();
	c2.Display();
	c3.Display();
	return 0;
}
