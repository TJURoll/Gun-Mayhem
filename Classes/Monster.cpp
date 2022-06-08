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
	dynamic_cast<Sprite*>(sprite->getChildByName("gun"))->setFlippedX(direction);//翻转枪械
}

void Monster::AIUpdate(float dt,const Vec2& posOfPlayer, Scene* scene)
{
	Vec2 posOfMonster = this->sprite->getPosition();//获取此时怪物位置
	static float stepTime = 0;
	static float fireTime = 0;
	static float jumpTime = 0; 
	static int fireTimeNum = 0;
	stepTime += dt;//定义AI检测的时间
	fireTime += dt;//定义开火检测的时间
	jumpTime += dt;//定义AI检测上下跳跃时间
	/*****************************每隔0.22秒，怪物将刷新一次，检测玩家位置，并且逐渐靠近**************************************/
	if (stepTime > 0.22)
	{
		//log("posOfPlayer.x=%f,posOfPlayer.y=%f,posOfMonster.x=%f,posOfMonster.y=%f", posOfPlayer.x, posOfPlayer.y, posOfMonster.x,posOfMonster.y);
		/*接下来是关于monster的动作*/

		/*首先将判断玩家的方向，怪物将面向玩家方向*/
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

		/*如果处于同一层怪物将朝着玩家方向水平移动*/
		if (fabs(posOfMonster.y - posOfPlayer.y) < 20)
		{
			/*当怪物位置在玩家的右边时，此时怪物将逐渐向右移动*/
			if ((posOfMonster.x - posOfPlayer.x) > 150)
			{
				Vec2 rePosition(-64, 0);
				auto moveBy = MoveBy::create(0.5f, rePosition);
				this->sprite->runAction(moveBy);
			}
			/*当怪物位置在玩家的左边时，此时怪物将逐渐向左移动*/
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
		/*此时怪物将检测自己是否中弹，如果中弹的话，将予以躲闪*/
		if (getShot())
		{
			MoveBy* dodgeMove;
			if (this->getDirection() && posOfPlayer.x < 1142)
				dodgeMove = MoveBy::create(0.5f, Vec2(100, 0));
			else if (!this->getDirection() && posOfPlayer.x > 300)
				dodgeMove = MoveBy::create(0.5f, Vec2(-100, 0));
			else
				return;
			auto DisableCollision = CallFunc::create([this]() {this->sprite->getPhysicsBody()->setCollisionBitmask(0b0000); });//不允许碰撞，防止穿模时出现的问题
			auto jump = MoveBy::create(0.5, Vec2(0, this->sprite->getContentSize().height * 2.6f));
			auto EnableCollision = CallFunc::create([this]() {this->sprite->getPhysicsBody()->setCollisionBitmask(0b0100); });//恢复原有的CollisionBitmask
			this->sprite->runAction(Spawn::create(DisableCollision, jump, EnableCollision, dodgeMove, nullptr));
		}
		if (posOfPlayer.y - posOfMonster.y > this->sprite->getContentSize().height && posOfPlayer.y < 880)
		{
			/*此时将检测AI是否处于边界，无法上跳，此时将采用斜上跳的方式进行*/
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
			
			/*此时AI将执行上跳*/
			auto DisableCollision = CallFunc::create([this]() {this->sprite->getPhysicsBody()->setCollisionBitmask(0b0000); });//不允许碰撞，防止穿模时出现的问题
			auto jump = MoveBy::create(0.5, Vec2(0, this->sprite->getContentSize().height * 2.6f));
			auto EnableCollision = CallFunc::create([this]() {this->sprite->getPhysicsBody()->setCollisionBitmask(0b0100); });//恢复原有的CollisionBitmask
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

	/*****************************每隔0.88秒，怪物将刷新一次，检测是否需要射击**************************************/
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


