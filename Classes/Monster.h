#ifndef _MONSTER_H_
#define _MONSTER_H_
#include "Entity.h"
#include "cocos2d.h"
#include"Weapon.h"

using namespace cocos2d;
class Monster :public Entity
{
public:
	Monster(std::string URL);
	Animation* removeRight();//���������ߵĶ���
	Animation* removeLeft();//���������ߵĶ���
	Animation* attack(Entity* entity);//���й����󷵻ض���
	Animation* getHurt(int hurtValue);//�⵽�����󷵻ض���
	void changeTexture(const bool direction);
	//�ı��ʱͼƬ����

	void AIUpdate(float dt, const Vec2& posOfPlayer, Scene* scene);
	bool getShot();
private:

protected:

};
#endif
