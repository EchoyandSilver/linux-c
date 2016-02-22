#include <iostream>
#include <stdlib.h>
using namespace std;

class Test
{
public:
	Test(int n) : n_(n)
	{
		cout<<"Test(int n) : n_(n)"<<endl;
	}
	Test(const Test& other)
	{
		cout<<"Test(const Test& other)"<<endl;
	}
	~Test()
	{
		cout<<"~Test()"<<endl;
	}

	void* operator new(size_t size)
	{
		cout<<" void* operator new(size_t size)"<<endl;
		void* p = malloc(size);
		return p;
	}

	void operator delete(void* p, size_t size)
	{
		cout<<"void operator delete(void* p), size_t size"<<endl;
		free(p);
	}
	void* operator new(size_t size, const char* file, long line)
	{
		cout<<file<<":"<<line<<endl;
		void* p = malloc(size);
		return p;
	}

	void operator delete(void* p, const char* file, long line)
	{
		cout<<file<<":"<<line<<endl;
		free(p);
	}

	void* operator new(size_t size, void* p)
	{
		return p;
	}

	void operator delete(void *, void *)
	{
		
	}

	int n_;
};

	void* operator new(size_t size)
	{
		cout<<"global void* operator new(size_t size)"<<endl;
		void* p = malloc(size);
		return p;
	}

	void operator delete(void* p)
	{
		cout<<"global void operator delete(void* p)"<<endl;
		free(p);
	}

	void* operator new[](size_t size)
	{
		cout<<"global void* operator new[](size_t size)"<<endl;
		void* p = malloc(size);
		return p;
	}

	void operator delete[](void* p)
	{
		cout<<"global void operator delete[](void* p)"<<endl;
		free(p);
	}


int main()
{
	Test* p1 = new Test(100); //new operator = operator new + 
	

	cout<<"delete[] +"<<endl;
	//delete[] p1;
	delete p1;

	cout<<"delete[] -"<<endl;
	char* str = new char[100];
	delete[] str;

	char chunk[10];

	Test* p2 = new (chunk) Test(200); // placement new
					  // operator new(size_t, void *_where)
	cout<<p2->n_<<endl;
	p2->~Test();

	//Test* p3 = (Test*)chunk;
	Test* p3 = reinterpret_cast<Test*>(chunk);
	cout<<p3->n_<<endl;
	
	Test* p4 = new(__FILE__,__LINE__)Test(300);

	return 0;
}
