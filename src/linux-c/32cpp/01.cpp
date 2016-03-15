#include <iostream>
using namespace std;

class Bed
{
public:
	Bed(int weight) : weight_(weight)
	{

	}
	void Sleep()
	{
		cout<<"Sleep..."<<endl;
	}
	int weight_;
};

class Sofa
{
public:
	Sofa(int weight) : weight_(weight)
	{

	}
	void WatchTV()
	{
		cout<<"Watch TV..."<<endl;
	}
	int weight_;
};

class SofaBed : public Bed, public Sofa
{
public:
	SofaBed() : Bed(0), Sofa(0)
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
	SofaBed sofabed;	
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
