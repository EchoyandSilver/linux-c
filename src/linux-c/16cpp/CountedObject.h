#ifndef _COUNTED_OBJECT_H_
#define _COUNTED_OBJECT_H_

class CountedObject
{
public:
	CountedObject();
	~CountedObject();
public:
	static int GetCount();
private:
	static int count_;
};

#endif  // _COUNTED_OBJECT_H_
