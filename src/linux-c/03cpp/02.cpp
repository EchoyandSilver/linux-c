#include <iostream>
using namespace std;

int main(void)
{
	int* p = new int(33);
	cout<<*p<<endl;

	int* p2 = new int[10];
	
	delete p;
	delete[] p2;
	return 0; 
}
