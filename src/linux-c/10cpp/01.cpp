#include <iostream>
using namespace std;

class Test
{
public:
	int num_;
};

//num_ =20;		Error
int num_ = 20;
int Add(int a, int b);

int main(void)
{
	int num_ = 30;
	{
		int num_ = 100; 
	}

	cout<<"num="<<num_<<endl;
	cout<<"num="<<::num_<<endl;
	return 0;
}

int Add(int a, int b)
{
	return a+b;
}

int test()
{
LABEL1:
	cout<<"label1"<<endl;
	goto LABEL3;
LABEL2:
	cout<<"label2"<<endl;
	goto LABEL1;
LABEL3:
	cout<<"label3"<<endl;
	goto LABEL2;
}
