#include <iostream>
using namespace std;

int main(void)
{
	const int val = 1024;
	const int& refval = val;
	
	//int& ref2 = val;
	
	//refval = 200;
	
	int val2 = 1024;
	const int& ref3 = val2;

	double val3 = 3.14;
	const int& ref4 = val3;
	
	cout<<"ref4="<<ref4<<endl;
	cout<<"ref3="<<ref3<<endl;

	//int& ref5 = val3;

	return 0;
}
