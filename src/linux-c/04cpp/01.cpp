#include <iostream>
using namespace std;

int main(void)
{
	int val = 100;
	//int& refval;
	int& refval = val;
	refval = 200;

	cout<<"val="<<val<<endl;
	
	int val2 = 500;
	refval = val2;

	cout<<"val="<<val<<endl;

	return 0;
}
