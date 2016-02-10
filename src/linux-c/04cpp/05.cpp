#include <iostream>
using namespace std;

int& add(int a, int b)
{
	int sum;
	sum = a + b;
	return sum;
}

int main(void)
{
	int n = add(3,4);
	int& n2 = add(5,6);
	
	cout<<"n2="<<n2<<endl;
	cout<<"n="<<n<<endl;
	cout<<"n2="<<n2<<endl;
	return 0;
}
