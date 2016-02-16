#include "Test.h"
#include <iostream>
using namespace std;

Test::Test() : num_(0)
{
	//num_ = 0;
	cout<<"Initializing Default"<<endl;
}

Test::Test(int num) : num_(num)
{
	//num_ = num;
	cout<<"Initializing"<< num_<<endl;
}

Test::Test(const Test& other) : num_(other.num_)
{
	//num_=other.num_;
	cout<<"Initializing with other"<<num_<<endl;
}

Test::~Test()
{
	cout<<"Destroy"<<num_<<endl;
}

void Test::Display()
{
	cout<<"num="<<num_<<endl;	
}

Test& Test::operator=(const Test& other)
{
	cout<<"Test::operator"<<endl;
	if(this == &other)	
		return *this;	

	num_=other.num_;
		return *this;
}
