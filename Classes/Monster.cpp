#include "Player.h"
#include "Monster.h"


Monster::Monster(std::string urlOfSpirite) :Entity(urlOfSpirite) {}


Animation* Monster::removeRight()
{
	return nullptr;
}

Animation* Monster::removeLeft()
{
	return nullptr;
}

Animation* Monster::attack(Entity* entity)
{
	return nullptr;
}

Animation* Monster::getHurt(int hurtValue)
{
	return nullptr;
}

void Monster::changeTexture(const bool direction)
{
	sprite->setFlippedX(direction);
	dynamic_cast<Sprite*>(sprite->getChildByName("gun"))->setFlippedX(direction);//��תǹе
}

void Monster::AIUpdate(float dt,const Vec2& posOfPlayer, Scene* scene)
{
	Vec2 posOfMonster = this->sprite->getPosition();//��ȡ��ʱ����λ��
	static float stepTime = 0;
	static float fireTime = 0;
	static float jumpTime = 0; 
	static int fireTimeNum = 0;
	stepTime += dt;//����AI����ʱ��
	fireTime += dt;//���忪�����ʱ��
	jumpTime += dt;//����AI���������Ծʱ��
	/*****************************ÿ��0.22�룬���ｫˢ��һ�Σ�������λ�ã������𽥿���**************************************/
	if (stepTime > 0.22)
	{
		//log("posOfPlayer.x=%f,posOfPlayer.y=%f,posOfMonster.x=%f,posOfMonster.y=%f", posOfPlayer.x, posOfPlayer.y, posOfMonster.x,posOfMonster.y);
		/*�������ǹ���monster�Ķ���*/

		/*���Ƚ��ж���ҵķ��򣬹��ｫ������ҷ���*/
		if (posOfMonster.x > posOfPlayer.x && !this->getDirection())
		{
			this->changeDirection(true);
			this->changeTexture(true);
		}
		if (posOfMonster.x < posOfPlayer.x && this->getDirection())
		{
			this->changeDirection(false);
			this->changeTexture(false);
		}

		/*�������ͬһ����ｫ������ҷ���ˮƽ�ƶ�*/
		if (fabs(posOfMonster.y - posOfPlayer.y) < 20)
		{
			/*������λ������ҵ��ұ�ʱ����ʱ���ｫ�������ƶ�*/
			if ((posOfMonster.x - posOfPlayer.x) > 150)
			{
				Vec2 rePosition(-64, 0);
				auto moveBy = MoveBy::create(0.5f, rePosition);
				this->sprite->runAction(moveBy);
			}
			/*������λ������ҵ����ʱ����ʱ���ｫ�������ƶ�*/
			else if (((posOfPlayer.x - posOfMonster.x) > 150))
			{
				Vec2 rePosition(64, 0);
				auto moveBy = MoveBy::create(0.5f, rePosition);
				this->sprite->runAction(moveBy);
			}

		}
		stepTime = 0;
	}

	if (jumpTime > 0.66f)
	{
		/*��ʱ���ｫ����Լ��Ƿ��е�������е��Ļ��������Զ���*/
		if (getShot())
		{
			MoveBy* dodgeMove;
			if (this->getDirection() && posOfPlayer.x < 1142)
				dodgeMove = MoveBy::create(0.5f, Vec2(100, 0));
			else if (!this->getDirection() && posOfPlayer.x > 300)
				dodgeMove = MoveBy::create(0.5f, Vec2(-100, 0));
			else
				return;
			auto DisableCollision = CallFunc::create([this]() {this->sprite->getPhysicsBody()->setCollisionBitmask(0b0000); });//��������ײ����ֹ��ģʱ���ֵ�����
			auto jump = MoveBy::create(0.5, Vec2(0, this->sprite->getContentSize().height * 2.6f));
			auto EnableCollision = CallFunc::create([this]() {this->sprite->getPhysicsBody()->setCollisionBitmask(0b0100); });//�ָ�ԭ�е�CollisionBitmask
			this->sprite->runAction(Spawn::create(DisableCollision, jump, EnableCollision, dodgeMove, nullptr));
		}
		if (posOfPlayer.y - posOfMonster.y > this->sprite->getContentSize().height && posOfPlayer.y < 880)
		{
			/*��ʱ�����AI�Ƿ��ڱ߽磬�޷���������ʱ������б�����ķ�ʽ����*/
			MoveBy* moveJump;
			//log("hello");
			if ((fabs(posOfMonster.y - 148) < 5.f && posOfMonster.x > 1272))
				moveJump= MoveBy::create(0.5, Vec2(-(posOfMonster.x - 1272)-15,0 ));
			else if ((fabs(posOfMonster.y - 323) < 5.f && posOfMonster.x > 1042))
				moveJump = MoveBy::create(0.5, Vec2(-(posOfMonster.x - 1042)-15, 0));
			else if ((fabs(posOfMonster.y - 480) < 5.f && posOfMonster.x > 816))
				moveJump = MoveBy::create(0.5, Vec2(-(posOfMonster.x - 816)-15, 0));
			else if ((fabs(posOfMonster.y - 637) < 5.f && posOfMonster.x > 634))
				moveJump = MoveBy::create(0.5, Vec2(-(posOfMonster.x - 625)-15, 0));
			else
				moveJump= MoveBy::create(0,Vec2(0,0));
			
			/*��ʱAI��ִ������*/
			auto DisableCollision = CallFunc::create([this]() {this->sprite->getPhysicsBody()->setCollisionBitmask(0b0000); });//��������ײ����ֹ��ģʱ���ֵ�����
			auto jump = MoveBy::create(0.5, Vec2(0, this->sprite->getContentSize().height * 2.6f));
			auto EnableCollision = CallFunc::create([this]() {this->sprite->getPhysicsBody()->setCollisionBitmask(0b0100); });//�ָ�ԭ�е�CollisionBitmask
			this->sprite->runAction(Spawn::create(DisableCollision, jump, EnableCollision, moveJump, nullptr));
		}
		else if (posOfMonster.y - posOfPlayer.y > this->sprite->getContentSize().height && posOfPlayer.y > 60
			&&posOfPlayer.x<1480&&posOfPlayer.x>82)
		{
			this->sprite->runAction(MoveBy::create(0.5, Vec2(0, -this->sprite->getContentSize().height * 2)));
		}
		jumpTime = 0;
	}

#if 1
#endif

	/*****************************ÿ��0.88�룬���ｫˢ��һ�Σ�����Ƿ���Ҫ���**************************************/
	if (fireTime > 0.6f)
	{
		if(fabs(posOfMonster.y-posOfPlayer.y)<20)
			dynamic_cast<Gun*>(sprite->getChildByName("gun"))->fire(scene, this);
		fireTime = 0;
	}
}

bool Monster::getShot()
{
	return false;
}


