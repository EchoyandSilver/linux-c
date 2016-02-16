#include "String.h"

int main(void)
{
	String s1("AAA");
	s1.Display();
	
	String s2 = s1;		//<==> s2.str_ = s1.str_;

	String s3;		
	s3.Display();
	s3 = s2;		//<==> s3.str_ = s2.str_;
	
				//s3.operator=(s2);
	return 0;
}
