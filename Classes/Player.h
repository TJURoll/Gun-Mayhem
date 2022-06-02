#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Entity.h"
#include "cocos2d.h"

using namespace cocos2d;
class Player :public Entity
{
public:
	Player(std::string URL);
	Animation* removeRight();//返回向右走的动画
	Animation* removeLeft();//返回向左走的动画
	Animation* attack(Entity* entity);//进行攻击后返回动画
	Animation* getHurt(int hurtValue);//遭到攻击后返回动画
	void changeTexture(const bool direction);//改变此时图片方向
private:
	
protected:
	
};
#endif