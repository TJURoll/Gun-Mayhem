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
	Animation* removeRight();//���������ߵĶ���
	Animation* removeLeft();//���������ߵĶ���
	Animation* attack(Entity* entity);//���й����󷵻ض���
	Animation* getHurt(int hurtValue);//�⵽�����󷵻ض���
	void changeTexture(const bool direction);//�ı��ʱͼƬ����
private:
	
protected:
	
};
#endif