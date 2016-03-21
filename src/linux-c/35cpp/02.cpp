#include <iostream>
using namespace std;

class Base
{
public:
	virtual ~Base() 
	{

	}
};

class Drived : public Base
{

};

int main(void)
{
	Drived d;
	return 0;
}
