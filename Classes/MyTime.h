#pragma once
#include "cocos2d.h"
#include <fstream>
using namespace std;
USING_NS_CC;
class Time:public Label
{
private:
	int minute;
	int second;
public:
	void timeUpdate();
	string timeShow();
	Time(const int& minute = 0,const int& second = 0) :minute(minute), second(second) {};
	void addClock(Scene* scene);

	CREATE_FUNC(Time);
	virtual bool init();

	operator int();
	friend ofstream& operator <<(ofstream& out, Time& time);
};