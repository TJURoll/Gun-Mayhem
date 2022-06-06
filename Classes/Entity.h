#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Entity:public Node
{
public:
	Entity(std::string url);
	Sprite* getSprite();
#if 1
	virtual Animation* removeRight()= 0;//���������ߵĶ���
	virtual Animation* removeLeft() = 0;//���������ߵĶ���
	virtual Animation* attack(Entity* entity) = 0;//���й����󷵻ض���
	virtual Animation* getHurt(int hurtValue) = 0;//�⵽�����󷵻ض���
#endif
	bool whetherCanMove(const Vec2 position);//�жϴ�ʱ�����Ƿ��ܹ��ƶ����˴�,���ڽ�����ײ��⺯��
	void bindSpirite(Sprite* _sprite);//�󶨾���

	bool getDirection(void);//��ȡ�����߷���,false���ң�true����
	void changeDirection(const bool);//�ı������߷���
	Sprite* sprite;
private:

protected:
	int lifeNum;
	bool direction = false;//�����ж��䷽��
	//CC_PROPERTY(int, m_lifeNum, lifeNum);

};