#pragma once
#include "cocos2d.h"

using namespace cocos2d;
class Player
{
public:
	bool whetherCanMove(const Vec2 position);//�жϴ�ʱ�����Ƿ��ܹ��ƶ����˴�
	Sprite* hero;
private:

protected:
	
};

class Hero1 :public Player//��һ���ܹ��ٿص�Ӣ��
{
public:
	Hero1(std::string urlOfPiture);
private:
	float hp = 0;
};