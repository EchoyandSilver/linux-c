#include <iostream>
using namespace std;

int a[] = {0, 1, 2, 3, 4};

int& index(int i)
{
	return a[i];
}

int main(void)
{
	index(3) = 100;
	
	cout<<"a[3]="<<a[3]<<endl;
	return 0;
}
