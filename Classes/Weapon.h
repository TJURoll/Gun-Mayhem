#pragma once
#include "cocos2d.h"
#include "Entity.h"
#include<algorithm>
USING_NS_CC;
class Gun :public Sprite
{
private:
	 const float MASS=10.f;
	float shootingInterval;
	int firepower;
	int bulletSpeed;
public:
	void stopAWhile(EventListener* Listener,float interval=0);
	void fire(Scene* scene, Entity* shooter);
	Gun(float shootingInterval, int firepower, int bulletSpeed);
	virtual void bindShooter(Sprite* shooter)=0;
	void throwExplosives(Scene* scene, Entity* shooter);
};
class MachineGun : public Gun
{
public:
	CREATE_FUNC(MachineGun);
	virtual bool init();
	MachineGun() :Gun(.05f, 3, 4000) {};
	virtual void bindShooter(Sprite* shooter);
};
class SniperGun :public  Gun
{
public:
	CREATE_FUNC(SniperGun);
	virtual bool init();
	SniperGun() :Gun(.6f, 15, 7000) {};
	virtual void bindShooter(Sprite* shooter);
};
class HandGun :public Gun
{
public:
	CREATE_FUNC(HandGun);
	virtual bool init();
	HandGun() :Gun(.3f, 8, 3000) {};
	virtual void bindShooter(Sprite* shooter);
};