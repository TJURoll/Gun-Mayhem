#pragma once
#include "cocos2d.h"
#include "Entity.h"
#include<algorithm>
#include "editor-support/cocostudio/SimpleAudioEngine.h"
USING_NS_CC;
class Gun :public Sprite
{
private:
	const float MASS = 10.f;
	float shootingInterval;//����������stopAWhile����ʵ��
	int firepower;//����Ч��
	int bulletSpeed;//�ӵ��ٶ�
public:
	Gun(float shootingInterval, int firepower, int bulletSpeed);
	virtual void bindShooter(Sprite* shooter) = 0;//��ǹ�ͽ�ɫ��
	void stopAWhile(EventListener* Listener, float interval = 0);
	void fire(Scene* scene, Entity* shooter);//����
	void throwExplosives(Scene* scene, Entity* shooter);//��ը��
};
class MachineGun : public Gun
{
public:
	MachineGun() :Gun(.05f, 3, 3000) {};
	CREATE_FUNC(MachineGun);
	virtual bool init();
	virtual void bindShooter(Sprite* shooter);
};
class SniperGun :public  Gun
{
public:
	SniperGun() :Gun(.6f, 15, 5000) {};
	CREATE_FUNC(SniperGun);
	virtual bool init();
	virtual void bindShooter(Sprite* shooter);
};
class HandGun :public Gun
{
public:
	HandGun() :Gun(.3f, 8, 2000) {};
	CREATE_FUNC(HandGun);
	virtual bool init();
	virtual void bindShooter(Sprite* shooter);
};