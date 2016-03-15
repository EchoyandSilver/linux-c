#include <iostream>
using namespace std;

class Furniture
{
public:
	Furniture(int weight) : weight_(weight)
	{

	}
	int weight_;
};

class Bed : public Furniture
{
public:
	Bed(int weight) : Furniture(weight)
	{

	}
	void Sleep()
	{
		cout<<"Sleep..."<<endl;
	}
};

class Sofa : public Furniture
{
public:
	Sofa(int weight) : Furniture(weight)
	{

	}
	void WatchTV()
	{
		cout<<"Watch TV..."<<endl;
	}
};

class SofaBed : public Bed, public Sofa
{
public:
	SofaBed(int weight) : Bed(weight), Sofa(weight)
	{
		FoldIn();
	}
	void FoldOut()
	{
		cout<<"FoldOut..."<<endl;
	}
	void FoldIn()
	{
		cout<<"FoldIn..."<<endl;
	}
};

int main(void)
{
	SofaBed sofabed(10);	
	//sofabed.weight_ = 10;
	//sofabed.weight_ = 20;
	
	sofabed.Bed::weight_ = 10;
	sofabed.Sofa::weight_ = 20;
	
	sofabed.WatchTV();
	sofabed.FoldOut();
	sofabed.Sleep();
	sofabed.FoldIn();
	return 0;
}
