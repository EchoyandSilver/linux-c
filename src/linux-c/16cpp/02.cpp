#include <iostream>
using namespace std;

class Test
{
public:
	Test()
	{

	}
	~Test()
	{
		
	}
	static const int x_ = 100;
};

//const int Test::x_;

int main(void)
{
	cout<<Test::x_<<endl;
}
