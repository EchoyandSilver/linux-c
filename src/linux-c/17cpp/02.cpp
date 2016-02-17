#include <iostream>
using namespace std;

class Test
{
public:
	Test(int n) : n_(n)
	{
		cout<<"Test"<<n_<<"..."<<endl;
	}
	~Test()
	{
		cout<<"~Test"<<n_<<"..."<<endl;
	}
private:
	int n_;
};
		
int n;				//.bss
int n2 = 100;			//.data
Test g(100);
static Test g2(200);

int main(void)
{
	cout<<"Entering main..."<<endl;
	cout<<n<<endl;
	Test t(10);
	{
		Test t(20);
	}

	{
	Test* t3 = new Test(30);
	delete t3;
	}

	{
		static int n3;		//.bss
		static int n4 = 100;	//.data

		static Test t4(333);	//.data
	}
	cout<<"Exiting main..."<<endl;
}
