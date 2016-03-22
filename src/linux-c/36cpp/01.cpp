#include <iostream>
#include <vector>
using namespace std;

class Shape
{
public:
	virtual void Draw() = 0;
	virtual ~Shape() {}
};

class Circle : public Shape
{
public:
	void Draw()
	{
		cout<<"Circle::Draw()..."<<endl;
	}
	~Circle()
	{
		cout<<"~Circle..."<<endl;
	}
};

class Square : public Shape
{
public:
	void Draw()
	{
		cout<<"Square::Draw()..."<<endl;
	}
	~Square()
	{
		cout<<"~Square..."<<endl;
	}
};

class Rectangle : public Shape
{
	void Draw()
	{
		cout<<"Rectangle::Draw()..."<<endl;
	}
	~Rectangle()
	{
		cout<<"~Rectangle..."<<endl;
	}

};

void DrawAllShapes(const vector<Shape*>& v)
{
	vector<Shape*>::const_iterator it;
	for(it=v.begin();it!=v.end();++it)
	{
		(*it)->Draw();
	}
}

void DeleteAllShapes(const vector<Shape*>& v)
{
	vector<Shape*>::const_iterator it;
	for(it=v.begin();it!=v.end();++it)
	{
		delete(*it);
	}
}

class ShapeFactory
{
public:
	static Shape* CreateShape(const string& name)
	{
		Shape* ps;
		if(name == "Circle")
		{
			ps = new Circle;
		}
		else if(name == "Square")
		{
			ps = new Square;
		}
		else if(name == "Rectangle")
		{
			ps = new Rectangle;
		}

		return ps;
	}
};

int main(void)
{
	vector<Shape*> v;

	Shape* ps;
	ps = ShapeFactory::CreateShape("Circle");
	v.push_back(ps);
	ps = ShapeFactory::CreateShape("Square");
	v.push_back(ps);
	ps = ShapeFactory::CreateShape("Rectangle");
	v.push_back(ps);
	
	DrawAllShapes(v);
	DeleteAllShapes(v);	

	return 0;
}
