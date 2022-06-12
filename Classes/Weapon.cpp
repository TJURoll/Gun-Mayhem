#include "Weapon.h"

Gun::Gun(const float& shootingInterval,const int& firepower,const int& bulletSpeed) :shootingInterval(shootingInterval), firepower(firepower), bulletSpeed(bulletSpeed) {}

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
	physicsBody->setVelocity(Vec2(direction ? -100.f : 100.f, 80.f));
	physicsBody->setCategoryBitmask(0b0110);
	physicsBody->setCollisionBitmask(0b1001);
	physicsBody->setContactTestBitmask(0b1001);
	explosive->setPhysicsBody(physicsBody);
	scene->addChild(explosive);

	//定时爆炸
	auto boom = CallFunc::create([=]() {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/boom.mp3");
		explosive->setTexture("explode.png");
		explosive->setScale(0.2f);
		explosive->setTag(-2); });
	auto swell = ScaleTo::create(.2f, 10);
	explosive->runAction(Sequence::create(DelayTime::create(2.5f), boom, swell, RemoveSelf::create(), nullptr));

}

void Gun::fire(Scene* scene, Entity* shooter)
{
	CCLOG("fire");
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/fire.mp3");
	auto bullet = Sprite::create("bullet.png");
	bool direction = shooter->getDirection();//向左为true,向右为false
	auto position = shooter->getSprite()->getPosition();
	bullet->setPosition(Vec2(position.x + (direction ? 60.f : -60.f), position.y));
	if (direction)
		bullet->setFlippedX(true);
	shooter->getSprite()->getPhysicsBody()->applyImpulse(Vec2(5 * MASS * (direction ? firepower : -firepower), 0));

	auto physicsBody = PhysicsBody::createBox(bullet->getContentSize(), PhysicsMaterial(0.f, 0.f, 0.0f));// 密度，修复，摩擦
	physicsBody->setVelocity(Vec2(static_cast<float>(direction ? -bulletSpeed : bulletSpeed), 0.f));
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

bool MachineGun::init()
{
	this->setTexture("guns.png");
	this->setTextureRect(Rect(-10.f, 0.f, 90.f, 27.f));
	return true;
}

void MachineGun::bindShooter(Sprite* shooter)
{
	this->setName("gun");
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	this->setScale(1.3f);
	this->setPosition(shooter->getContentSize() / 2);
	shooter->addChild(this);
}


bool SniperGun::init()
{
	this->setTexture("guns.png");
	this->setTextureRect(Rect(-10.f, 85.f, 100.f, 27.f));
	return true;
}

void SniperGun::bindShooter(Sprite* shooter)
{
	this->setName("gun");
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	this->setScale(1.3f);
	auto size = shooter->getContentSize();
	this->setPosition(Vec2(size.width / 2, size.height / 2 - 8));
	shooter->addChild(this);
}

bool HandGun::init()
{
	this->setTexture("handgun.png");
	this->setTextureRect(Rect(-20.f, 0.f, 100.f, 40.f));
	return true;
}

void HandGun::bindShooter(Sprite* shooter)
{
	this->setName("gun");
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	this->setScale(0.8f);
	auto size = shooter->getContentSize();
	this->setPosition(Vec2(size.width / 2, size.height / 2 - 15));
	shooter->addChild(this);
}
