#include "Test.h"
#include <iostream>
using namespace std;

Test::Test()
{
	num_ = 0;
	cout<<"Initializing Default"<<endl;
}

Test::Test(int num)
{
	num_ = num;
	cout<<"Initializing"<< num_<<endl;
}

Test::~Test()
{
	cout<<"Destroy"<<num_<<endl;
}

void Test::Display()
{
	cout<<"num="<<num_<<endl;	
}
