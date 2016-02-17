#include "CountedObject.h"

int CountedObject::count_ = 0;

CountedObject::CountedObject()
{
	++count_;
}

CountedObject::~CountedObject()
{
	--count_;
}

int CountedObject::GetCount()
{
	return count_;
}
