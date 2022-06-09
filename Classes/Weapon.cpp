#include "Weapon.h"

void Gun::stopAWhile(EventListener* Listener, float interval) {
	if (!interval)
		interval = this->shootingInterval;
	Listener->setEnabled(false);
	auto delay = DelayTime::create(interval);
	auto startListener = CallFunc::create([=]() {Listener->setEnabled(true); });
	runAction(Sequence::create(delay, startListener, nullptr));
}
void Gun::throwExplosives(Scene* scene, Entity* shooter)
{
	auto explosive = Sprite::create("explosive.png");
	bool direction = shooter->getDirection();//向左为true,向右为false
	auto position = shooter->getSprite()->getPosition();
	explosive->setPosition(Vec2(position.x + (direction ? -50 : 50), position.y));
	auto physicsBody = PhysicsBody::createBox(explosive->getContentSize(), PhysicsMaterial(100.f, 1.f, 0.0f));// 密度，修复，摩擦
	physicsBody->setVelocity(Vec2(direction ? -100 : 100, 80));
	physicsBody->setCategoryBitmask(0b0110);
	physicsBody->setCollisionBitmask(0b1001);
	physicsBody->setContactTestBitmask(0b1001);
	explosive->setPhysicsBody(physicsBody);
	scene->addChild(explosive);

	//定时爆炸
	auto boom = CallFunc::create([=]() {
		explosive->setTexture("explode.png");
		explosive->setScale(0.2);
		explosive->setTag(-2); });
	auto swell = ScaleTo::create(.2f, 10);
	explosive->runAction(Sequence::create(DelayTime::create(2.5f), boom, swell, RemoveSelf::create(), nullptr));

}


void Gun::fire(Scene* scene, Entity* shooter)
{
	CCLOG("fire");

	auto bullet = Sprite::create("bullet.png");
	bool direction = shooter->getDirection();//向左为true,向右为false
	auto position = shooter->getSprite()->getPosition();
	bullet->setPosition(Vec2(position.x + (direction ? 70 : -70), position.y));
	if (direction)
		bullet->setFlippedX(true);
	shooter->getSprite()->getPhysicsBody()->applyImpulse(Vec2(5 * MASS * (direction ? firepower : -firepower), 0));

	auto physicsBody = PhysicsBody::createBox(bullet->getContentSize(), PhysicsMaterial(0.f, 0.f, 0.0f));// 密度，修复，摩擦
	physicsBody->setVelocity(Vec2(direction ? -bulletSpeed : bulletSpeed, 0));
	physicsBody->setGravityEnable(false);
	physicsBody->setRotationEnable(false);
	if ((shooter->getSprite()->getTag()) / 10 == 0)//我方子弹
	{
		physicsBody->setCategoryBitmask(0b10010);
		physicsBody->setCollisionBitmask(0b1000);
		physicsBody->setContactTestBitmask(0b1000);
	}
	else//敌方子弹
	{
		CCLOG("enemy");
		physicsBody->setCategoryBitmask(0b10100);
		physicsBody->setCollisionBitmask(0b0001);
		physicsBody->setContactTestBitmask(0b0001);
	}
	bullet->setPhysicsBody(physicsBody);
	std::string str(1, static_cast<char>(firepower));
	bullet->setName(str);
	bullet->setTag(-3);
	scene->addChild(bullet);
}

Gun::Gun(float shootingInterval, int firepower, int bulletSpeed) :shootingInterval(shootingInterval), firepower(firepower), bulletSpeed(bulletSpeed) {}



bool MachineGun::init()
{
	this->setTexture("guns.png");
	this->setTextureRect(Rect(-10, 0, 90, 27));
	return true;
}

void MachineGun::bindShooter(Sprite* shooter)
{
	this->setName("gun");
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	this->setScale(1.3);
	this->setPosition(shooter->getContentSize() / 2);
	shooter->addChild(this);
}


bool SniperGun::init()
{
	this->setTexture("guns.png");
	this->setTextureRect(Rect(-10, 85, 100, 27));
	return true;
}

void SniperGun::bindShooter(Sprite* shooter)
{
	this->setName("gun");
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	this->setScale(1.3);
	auto size = shooter->getContentSize();
	this->setPosition(Vec2(size.width / 2, size.height / 2 - 8));
	shooter->addChild(this);
}

bool HandGun::init()
{
	this->setTexture("handgun.png");
	this->setTextureRect(Rect(-20, 0, 100, 40));
	return true;
}

void HandGun::bindShooter(Sprite* shooter)
{
	this->setName("gun");
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	this->setScale(0.8);
	auto size = shooter->getContentSize();
	this->setPosition(Vec2(size.width / 2, size.height / 2 - 15));
	shooter->addChild(this);
}
