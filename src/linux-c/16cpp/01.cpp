#include "CountedObject.h"
#include <iostream>
using namespace std;

int main(void)
{
	//cout<<CountedObject::count_<<endl;
	cout<<CountedObject::GetCount()<<endl;
	CountedObject co1;
	cout<<CountedObject::GetCount()<<endl;
	CountedObject* co2 = new CountedObject;
	cout<<CountedObject::GetCount()<<endl;
	delete co2;
	cout<<CountedObject::GetCount()<<endl;
}