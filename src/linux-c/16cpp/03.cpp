#include <iostream>
using namespace std;

class Test
{
public:
	Test(int y) : y_(y)
	{

	}
	~Test()
	{
		
	}
	
	void TestFun()
	{
		cout<<"x="<<x_<<endl;	//Ok
		TestStaticFun();	//Ok
	}

	static void TestStaticFun()	//not *this
	{
		cout<<"TestStativFun..."<<endl;
		//TestFun();		//Error
		//cout<<"y="<<y_<<endl;	//Error
	}

	static int x_;
	int y_;
};

int Test::x_ = 100;;

int main(void)
{
	Test t(10);
	cout<<Test::x_<<endl;
	t.TestFun();

	//cout<<t.x_<<endl;
}
