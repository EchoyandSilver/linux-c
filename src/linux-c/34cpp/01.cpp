#include <iostream>
using namespace std;

class Base
{
public:
	virtual void Fun1()
	{
		cout<<"Base::Fun1..."<<endl;
	}

	virtual void Fun2()
	{
		cout<<"Base::Fun2..."<<endl;
	}
	
	void Fun3()
	{
		cout<<"Base::Fun3..."<<endl;
	}
};

class Derived : public Base
{
public:
	virtual void Fun1()
	{
		cout<<"Derived::Fun1..."<<endl;
	}

	virtual void Fun2()
	{
		cout<<"Derived::Fun2..."<<endl;
	}

	void Fun3()
	{
		cout<<"Derived::Fun3..."<<endl;
	}
};

int main(void)
{
	Base* p;
	Derived d;
	
	p = &d;
	p->Fun1();
	p->Fun2();
	p->Fun3();		

	return 0;
}
