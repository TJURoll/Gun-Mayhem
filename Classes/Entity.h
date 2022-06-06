#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Entity:public Node
{
public:
	Entity(std::string url);
	Sprite* getSprite();
#if 1
	virtual Animation* removeRight()= 0;//返回向右走的动画
	virtual Animation* removeLeft() = 0;//返回向左走的动画
	virtual Animation* attack(Entity* entity) = 0;//进行攻击后返回动画
	virtual Animation* getHurt(int hurtValue) = 0;//遭到攻击后返回动画
#endif
	bool whetherCanMove(const Vec2 position);//判断此时精灵是否能够移动到此处,后期接上碰撞检测函数
	void bindSpirite(Sprite* _sprite);//绑定精灵

	bool getDirection(void);//获取其行走方向,false向右，true向左
	void changeDirection(const bool);//改变其行走方向
	Sprite* sprite;
private:

protected:
	int lifeNum;
	bool direction = false;//用于判断其方向
	//CC_PROPERTY(int, m_lifeNum, lifeNum);

};