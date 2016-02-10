#include <iostream>
using namespace std;
#include <stdio.h>

#pragma pack(2)
struct Test
{
	char a;
	double b;
	char c;
};
#pragma pack()

int main(void)
{
	Test test;
	//&test = &test.a;
	char *p = (char*)&test;
	//cout<<p<<endl;
	printf("p=%p\n", p);
	p = &test.a;
	printf("p=%p\n", p);
	
	cout<<sizeof(Test)<<endl;
	return 0;
}
