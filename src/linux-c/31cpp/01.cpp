#include <iostream>
#include <string>
using namespace std;

class Employee
{
public:
	Employee(const string& name, const int age, const int deptno) : name_(name), age_(age), deptno_(deptno)
	{
	
	}
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
private:
	int level_;
};

class Manager2 : private Employee
{
public:
	Manager2(const string& name, const int age, const int deptno, int level) : Employee(name, age, deptno), level_(level)
	{

	}
private:
	int level_;
};

int main(void)
{
	Employee e1("zhangsan", 25, 20);
	Manager m1("lisi", 38, 20, 10);
	Manager2 m2("lisi", 38, 20, 10);
	Employee* pe;
	Manager* pm;
	Manager2* pm2;

	pe = &e1;
	pm = &m1;
	pm2 = &m2;
	
	pe = &m1;
	//pm = &e1;	Error

	//pe = pm2;	Error
	pe = reinterpret_cast<Employee*>(pm2);

	//e1 = m2;	Error
	//e1 = reinterpret_cast<Employee>(m2);

	pm = static_cast<Manager*>(pe);

	//m1 = reinterpret_cast<Manager>e1;

	return 0;
}
