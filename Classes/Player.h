#pragma once
#include "cocos2d.h"

using namespace cocos2d;
class Player
{
public:
	bool whetherCanMove(const Vec2 position);//判断此时精灵是否能够移动到此处
	Sprite* hero;
private:

protected:
	
};

class Hero1 :public Player//第一个能够操控的英雄
{
public:
	Hero1(std::string urlOfPiture);
private:
	float hp = 0;
};