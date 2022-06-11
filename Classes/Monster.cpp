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
			dodgeMove(posOfPlayer);
		}
		if (posOfPlayer.y - posOfMonster.y > this->sprite->getContentSize().height && posOfPlayer.y < 880)
		{
			/*此时将检测AI是否处于边界，无法上跳，此时将采用斜上跳的方式进行*/
			MoveBy* moveJump;
			//log("hello");
			if ((fabs(posOfMonster.y - 148) < 5.f && posOfMonster.x > 1172))
				moveJump= MoveBy::create(0.5, Vec2(-(posOfMonster.x - 1172)-15,0 ));
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
			auto EnableCollision = CallFunc::create([this]() {this->sprite->getPhysicsBody()->setCollisionBitmask(0b0010); });//恢复原有的CollisionBitmask
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
	bool getShot = false;
	//auto listenerPhysics = EventListenerPhysicsContact::create();
	//listenerPhysics->onContactBegin = [this,&getShot](PhysicsContact& contact)
	//{
	//	Node* node[2] = { contact.getShapeA()->getBody()->getNode() ,contact.getShapeB()->getBody()->getNode() };
	//	if (node[0] && node[1])
	//	{
	//		int tag[2] = { node[0]->getTag(),node[1]->getTag() };
	//		for (int i = 0; i < 2; i++)
	//			if (tag[i] == -3 && tag[!i] == 10)//多个AI设计时这里写本怪物的tag
	//				getShot = true;
	//	}

	//	return true;
	//};
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerPhysics, this);
	return getShot;
}

void Monster::dodgeMove(const Vec2& posOfPlayer)
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
	auto EnableCollision = CallFunc::create([this]() {this->sprite->getPhysicsBody()->setCollisionBitmask(0b0010); });//恢复原有的CollisionBitmask
	this->sprite->runAction(Spawn::create(DisableCollision, jump, EnableCollision, dodgeMove, nullptr));
}

void doubleAIcontrol(const Vec2& posOfPlayer, Monster* ai1, Monster* ai2, float dt, Scene* scene)
{
	/*
	*初始化时此时怪物1是主位，怪物2是将随机对玩家进行两面包夹芝士
	*/
	static Monster* monsterFirst = ai1;
	static Monster* monsterSecond = ai2;

	Vec2 posOfMonster1 = monsterFirst->sprite->getPosition();//获取此时怪物1位置
	Vec2 posOfMonster2 = monsterSecond->sprite->getPosition();//获取此时怪物2位置
	static float stepTime = 0;
	static float fireTime = 0;
	static int fireTimeNum = 0;
	stepTime += dt;

	/*此时会根据是否在场，交换主位*/
	if (ai1->getPosition().y < 0 && ai2->getPosition().y>0)
	{
		monsterFirst = ai2;
		monsterSecond = ai1;
	}
	else if (ai1->getPosition().y > 0 && ai2->getPosition().y < 0)
	{
		monsterFirst = ai1;
		monsterSecond = ai2;
	}



	/*首先将判断玩家的方向，怪物将面向玩家方向*/

	//怪物1
	if (posOfMonster1.x > posOfPlayer.x && !monsterFirst->getDirection())
	{
		monsterFirst->changeDirection(true);
		monsterFirst->changeTexture(true);
	}

	if (posOfMonster1.x < posOfPlayer.x && monsterFirst->getDirection())
	{
		monsterFirst->changeDirection(false);
		monsterFirst->changeTexture(false);
	}

	//怪物2
	if (posOfMonster2.x > posOfPlayer.x && !monsterSecond->getDirection())
	{
		monsterSecond->changeDirection(true);
		monsterSecond->changeTexture(true);
	}

	if (posOfMonster2.x < posOfPlayer.x && monsterSecond->getDirection())
	{
		monsterSecond->changeDirection(false);
		monsterSecond->changeTexture(false);
	}

	if (stepTime > 0.44)
	{
		/*如果处于同一层的怪物将朝着玩家方向水平移动*/
		if (fabs(posOfMonster1.y - posOfPlayer.y) < 20)
		{
			/*当怪物位置在玩家的右边时，此时怪物将逐渐向右移动*/
			if ((posOfMonster1.x - posOfPlayer.x) > 150)
			{
				Vec2 rePosition(-64, 0);
				auto moveBy = MoveBy::create(0.5f, rePosition);
				monsterFirst->sprite->runAction(moveBy);
			}
			/*当怪物位置在玩家的左边时，此时怪物将逐渐向左移动*/
			else if (((posOfPlayer.x - posOfMonster1.x) > 150))
			{
				Vec2 rePosition(64, 0);
				auto moveBy = MoveBy::create(0.5f, rePosition);
				monsterFirst->sprite->runAction(moveBy);
			}
		}

		if (fabs(posOfMonster2.y - posOfPlayer.y) < 20)
		{
			/*当怪物位置在玩家的右边时，此时怪物将逐渐向右移动*/
			if ((posOfMonster2.x - posOfPlayer.x) > 150)
			{
				Vec2 rePosition(-64, 0);
				auto moveBy = MoveBy::create(0.5f, rePosition);
				monsterSecond->sprite->runAction(moveBy);
			}
			/*当怪物位置在玩家的左边时，此时怪物将逐渐向左移动*/
			else if (((posOfPlayer.x - posOfMonster2.x) > 150))
			{
				Vec2 rePosition(64, 0);
				auto moveBy = MoveBy::create(0.5f, rePosition);
				monsterSecond->sprite->runAction(moveBy);
			}
		}



		/*此时如果处于交火状态时，从AI可能可以跳到玩家的背后进行攻击*/
		if (posOfMonster1.x <= posOfPlayer.x && posOfMonster2.x > 0 && posOfMonster2.x < 1300 && posOfMonster2.x <= posOfPlayer.x && fabs(posOfMonster2.y - posOfPlayer.y) < 20)
		{
			if (posOfPlayer.x < 900)
			{
				/*此时从AI可以进行跳跃，而不用担心跳下边界的问题*/
				float distance = posOfPlayer.x - posOfMonster2.x;

				auto moveX1 = MoveBy::create(0.5, Vec2(140, 0));
				auto movejump = MoveBy::create(0.5, Vec2(0, monsterSecond->sprite->getContentSize().height * 2.6f));

				if (distance > 100)
				{
					/*此时AI可以考虑不能仅仅只进行跳跃，而需要进行水平移动*/
					auto moveX2 = MoveBy::create(0.5, Vec2(distance - 100, 0));
					monsterSecond->sprite->runAction(Sequence::create(Spawn::create(moveX1, movejump, nullptr), moveX2, nullptr));
				}
				else
					monsterSecond->sprite->runAction(Spawn::create(moveX1, movejump, nullptr));

			}
		}
		else if (posOfMonster1.x >= posOfPlayer.x && posOfMonster2.x > 0 && posOfMonster2.x < 1300 && posOfMonster2.x >= posOfPlayer.x && fabs(posOfMonster2.y - posOfPlayer.y) < 20)
		{
			if ((posOfMonster2.y > 480 && posOfPlayer.x > 400) || (posOfMonster2.y <= 480 && posOfPlayer.x > 300))
			{
				/*此时从AI可以进行跳跃，而不用担心跳下边界的问题*/
				float distance = posOfMonster2.x - posOfPlayer.x;

				auto moveX1 = MoveBy::create(0.5, Vec2(-140, 0));
				auto movejump = MoveBy::create(0.5, Vec2(0, monsterSecond->sprite->getContentSize().height * 2.6f));

				if (distance > 100)
				{
					/*此时AI可以考虑不能仅仅只进行跳跃，而需要进行水平移动*/
					auto moveX2 = MoveBy::create(0.5, Vec2(100 - distance, 0));
					monsterSecond->sprite->runAction(Sequence::create(Spawn::create(moveX1, movejump, nullptr), moveX2, nullptr));
				}
				else
					monsterSecond->sprite->runAction(Spawn::create(moveX1, movejump, nullptr));
			}
		}

		if (posOfPlayer.y - posOfMonster1.y > monsterFirst->sprite->getContentSize().height && posOfPlayer.y < 880)
		{
			/*此时将检测AI是否处于边界，无法上跳，此时将采用斜上跳的方式进行*/
			MoveBy* moveJump;
			//log("hello");
			if ((fabs(posOfMonster1.y - 148) < 5.f && posOfMonster1.x > 1172))
				moveJump = MoveBy::create(0.5, Vec2(-(posOfMonster1.x - 1272) - 105, 0));
			else if ((fabs(posOfMonster1.y - 323) < 5.f && posOfMonster1.x > 1042))
				moveJump = MoveBy::create(0.5, Vec2(-(posOfMonster1.x - 1042) - 85, 0));
			else if ((fabs(posOfMonster1.y - 480) < 5.f && posOfMonster1.x > 816))
				moveJump = MoveBy::create(0.5, Vec2(-(posOfMonster1.x - 816) - 75, 0));
			else if ((fabs(posOfMonster1.y - 637) < 5.f && posOfMonster1.x > 634))
				moveJump = MoveBy::create(0.5, Vec2(-(posOfMonster1.x - 625) - 45, 0));
			else
				moveJump = MoveBy::create(0.5, Vec2(0, 0));

			/*此时AI将执行上跳*/
			auto jump = MoveBy::create(0.5, Vec2(0, monsterFirst->sprite->getContentSize().height * 2.8f));
			monsterFirst->sprite->runAction(Spawn::create(jump, moveJump, nullptr));
		}
		else if (posOfMonster1.y - posOfPlayer.y > monsterFirst->sprite->getContentSize().height && posOfPlayer.y > 60
			&& posOfPlayer.x < 1480 && posOfPlayer.x>82)
		{
			monsterFirst->sprite->runAction(MoveBy::create(0.5, Vec2(0, -monsterFirst->sprite->getContentSize().height * 2)));
		}

		if (posOfPlayer.y - posOfMonster2.y > monsterSecond->sprite->getContentSize().height && posOfPlayer.y < 880)
		{
			/*此时将检测AI是否处于边界，无法上跳，此时将采用斜上跳的方式进行*/
			MoveBy* moveJump;
			//log("hello");
			if ((fabs(posOfMonster2.y - 148) < 5.f && posOfMonster2.x > 1172))
				moveJump = MoveBy::create(0.5, Vec2(-(posOfMonster2.x - 1272) - 105, 0));
			else if ((fabs(posOfMonster2.y - 323) < 5.f && posOfMonster2.x > 1042))
				moveJump = MoveBy::create(0.5, Vec2(-(posOfMonster2.x - 1042) - 85, 0));
			else if ((fabs(posOfMonster2.y - 480) < 5.f && posOfMonster2.x > 816))
				moveJump = MoveBy::create(0.5, Vec2(-(posOfMonster2.x - 816) - 75, 0));
			else if ((fabs(posOfMonster2.y - 637) < 5.f && posOfMonster2.x > 634))
				moveJump = MoveBy::create(0.5, Vec2(-(posOfMonster2.x - 625) - 45, 0));
			else
				moveJump = MoveBy::create(0.5, Vec2(0, 0));

			/*此时AI将执行上跳*/
			auto jump = MoveBy::create(0.5, Vec2(0, monsterSecond->sprite->getContentSize().height * 2.8f));
			monsterSecond->sprite->runAction(Spawn::create(jump, moveJump, nullptr));
		}
		else if (posOfMonster2.y - posOfPlayer.y > monsterSecond->sprite->getContentSize().height && posOfPlayer.y > 60
			&& posOfPlayer.x < 1480 && posOfPlayer.x>82)
		{
			monsterSecond->sprite->runAction(MoveBy::create(0.5, Vec2(0, -monsterSecond->sprite->getContentSize().height * 2)));
		}


		stepTime = 0;
	}

	/*****************************每隔0.88秒，怪物将刷新一次，检测是否需要射击**************************************/
	if ((fireTime > 0.6f && fireTimeNum != 0) || (fireTimeNum == 0 && fireTime > 3.f))
	{
		/*此时会检查避免重叠互相射击*/

		if (fabs(posOfMonster1.y - posOfPlayer.y) < 20
			&& (((monsterFirst->getDirection() == false) && (posOfMonster1.x > posOfMonster2.x)) || ((monsterFirst->getDirection() == true) && (posOfMonster1.x < posOfMonster2.x))))
			dynamic_cast<Gun*>(monsterFirst->sprite->getChildByName("gun"))->fire(scene, monsterFirst);

		if (fabs(posOfMonster2.y - posOfPlayer.y) < 20
			&& (((monsterSecond->getDirection() == false) && (posOfMonster2.x > posOfMonster1.x)) || ((monsterSecond->getDirection() == true) && (posOfMonster2.x < posOfMonster1.x))))
			dynamic_cast<Gun*>(monsterSecond->sprite->getChildByName("gun"))->fire(scene, monsterSecond);


		fireTime = 0;
		fireTimeNum++;
	}

}
