#include "Weapon.h"
Vec2 operator -(Vec2 v1, Vec2 v2)
{
	return Vec2(v1.x - v2.x, v1.y - v2.y);
}
float operator &(Vec2 v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}
void Gun::stopAWhile(EventListener* Listener,float interval) {
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
	explosive->setPosition(Vec2(position.x + (direction ? -50 : 50),position.y));
	auto physicsBody = PhysicsBody::createBox(explosive->getContentSize(), PhysicsMaterial(100.f, 1.f, 0.0f));// 密度，修复，摩擦
	physicsBody->setVelocity(Vec2(direction ? -100 : 100, 80));
	physicsBody->setCategoryBitmask(0b1111);
	physicsBody->setContactTestBitmask(0b1111);
	explosive->setPhysicsBody(physicsBody);
	scene->addChild(explosive);
	auto boom = CallFunc::create([=]() {
		explosive->setTexture("explode.png");
		explosive->setScale(0.2);
		explosive->setTag(-2); });
	auto swell = ScaleTo::create(.2f, 10);
	explosive->runAction(Sequence::create(DelayTime::create(2.5f),boom, swell, RemoveSelf::create(), nullptr));

}
void Gun::addContactListener()
{
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [this](PhysicsContact& contact) {
		Node* node[2] = { contact.getShapeA()->getBody()->getNode() ,contact.getShapeB()->getBody()->getNode() };
		if (node[0] && node[1])
		{
			int tag[2] = { node[0]->getTag(),node[1]->getTag() };
			for (int i = 0; i < 2; i++)
			{
				if (tag[i] == -2)
				{

					node[!i]->getPhysicsBody()->applyImpulse(Vec2((node[!i]->getPosition().x - node[i]->getPosition().x < 0 ? -400 : 400)*MASS, 100*MASS));
					break;
				}
				if (tag[i] == -3)
				{
					node[!i]->getPhysicsBody()->applyImpulse(Vec2(30* MASS*(node[!i]->getPosition().x - node[i]->getPosition().x < 0 ? -firepower : firepower), 0));
					auto boomEffect = [node, i]() {
						dynamic_cast<Sprite*>(node[i])->setTexture("explodeboom.png");
						node[i]->getPhysicsBody()->setDynamic(false);
					};
					node[i]->runAction(Sequence::create(CallFunc::create(boomEffect), DelayTime::create(.1f), RemoveSelf::create(), nullptr));
					break;
				}
			}

			CCLOG("onContact!!  tagA = %d, tagB = %d", tag[0], tag[1]);
		}
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}
void Gun::fire(Scene* scene, Entity* shooter) {
	CCLOG("fire");

	auto bullet = Sprite::create("bullet.png");
	bool direction = shooter->getDirection();//向左为true,向右为false
	auto position = shooter->getSprite()->getPosition();
	bullet->setPosition(Vec2(position.x + (direction ? -20 : 20), position.y));
	if (direction)
		bullet->setFlippedX(true);
	shooter->getSprite()->getPhysicsBody()->applyImpulse(Vec2(5*MASS*(direction ?firepower : -firepower),0));

	auto physicsBody = PhysicsBody::createBox(bullet->getContentSize(), PhysicsMaterial(100.f, 0.f, 0.0f));// 密度，修复，摩擦
	physicsBody->setVelocity(Vec2(direction ? -bulletSpeed : bulletSpeed, 0));
	physicsBody->setGravityEnable(false);
	physicsBody->setRotationEnable(false);
	physicsBody->setCategoryBitmask(0b1111);
	physicsBody->setContactTestBitmask(0b1111);
	bullet->setPhysicsBody(physicsBody);
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
	this->setPosition(Vec2(size.width / 2,size.height/2-8));
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
