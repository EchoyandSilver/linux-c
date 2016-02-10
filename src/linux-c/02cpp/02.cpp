#include <iostream>
using namespace std;

int main(void)
{
	//const int a;
	const int a = 100;
	//a = 200;
	
	int b = 22;
	const int *p;
	p = &b;
	//*p = 200;
	//int * const p2 = &b;
	int c = 100;
	//p2 = &c;
	*p2 = 200;

	cout<<b<<endl;

	return 0;
}
