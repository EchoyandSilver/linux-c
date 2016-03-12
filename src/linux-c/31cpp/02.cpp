#include <iostream>
#include <string>
using namespace std;


class Manager;
class Employee
{
public:
	Employee(const string& name, const int age, const int deptno) : name_(name), age_(age), deptno_(deptno)
	{
	
	} 

	operator Manager();
private:
	string name_;
	int age_;
	int deptno_;
};

class Manager : public Employee
{
public:
	Manager(const string& name, const int age, const int deptno, int level) : Employee(name, age, deptno), level_(level)
	{

	}

	Manager(const Employee& other) : Employee(other), level_(-1)
	{

	}

private:
	int level_;
};

Employee :: operator Manager()
{
	return Manager(name_, age_, deptno_, -1);
}

int main(void)
{
	Employee e1("zhangsan", 25, 20);
	Manager m1("lisi", 38, 20, 10);

	m1 = e1;

	return 0;
}
