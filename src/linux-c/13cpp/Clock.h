//#pragma once
#ifndef _CLOCK_H_
#define _CLOCK_H_

class Clock
{
public:
	void Display();
	Clock(int hour=0, int minute=0, int second=0);
	~Clock();
	void Updata();
	
	int GetHour();
	int GetMinute();
	int GetSecond();

	void SetHour(int hour);
	void SetMinute(int minute);
	void SetSecond(int second);
private:
	int hour_;
	int minute_;
	int second_;
};

#endif // _CLOCK_H_
