#include "MyTime.h"

void Time::timeUpdate()
{
	second++;
	if (second == 60)
	{
		minute++;
		second = 0;
	}
	this->setString("TIME  "+timeShow());
}

string Time::timeShow()
{
	return std::to_string(minute) + ":" + std::to_string(second);
}

void Time::addClock(Scene* scene)
{
	this->setPosition(scene->getContentSize());
	this->setScale(4.f);
	scene->addChild(this);
	
}

bool Time::init()
{
	this->setName("clock");
	this->setTextColor(Color4B::GRAY);
	this->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	return true;
}

Time::operator int()
{
	return minute * 60 + second;
}


ofstream& operator<<(ofstream& out, Time& time)
{
	out << time.timeShow();
	return out;
}
