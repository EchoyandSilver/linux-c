#ifndef _TEST_H_
#define _TEST_H_

class Test
{
public:
	/*explicit*/ Test(int num);
	Test();
	
	Test(const Test& other);

	void Display();
	
	Test& operator=(const Test& other);
	
	~Test();
private:
	int num_;
};
#endif	//_TEST_H_
