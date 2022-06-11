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
			dodgeMove(posOfPlayer);
		}
		if (posOfPlayer.y - posOfMonster.y > this->sprite->getContentSize().height && posOfPlayer.y < 880)
		{
			/*��ʱ�����AI�Ƿ��ڱ߽磬�޷���������ʱ������б�����ķ�ʽ����*/
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
			
			/*��ʱAI��ִ������*/
			auto DisableCollision = CallFunc::create([this]() {this->sprite->getPhysicsBody()->setCollisionBitmask(0b0000); });//��������ײ����ֹ��ģʱ���ֵ�����
			auto jump = MoveBy::create(0.5, Vec2(0, this->sprite->getContentSize().height * 2.6f));
			auto EnableCollision = CallFunc::create([this]() {this->sprite->getPhysicsBody()->setCollisionBitmask(0b0010); });//�ָ�ԭ�е�CollisionBitmask
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
	bool getShot = false;
	//auto listenerPhysics = EventListenerPhysicsContact::create();
	//listenerPhysics->onContactBegin = [this,&getShot](PhysicsContact& contact)
	//{
	//	Node* node[2] = { contact.getShapeA()->getBody()->getNode() ,contact.getShapeB()->getBody()->getNode() };
	//	if (node[0] && node[1])
	//	{
	//		int tag[2] = { node[0]->getTag(),node[1]->getTag() };
	//		for (int i = 0; i < 2; i++)
	//			if (tag[i] == -3 && tag[!i] == 10)//���AI���ʱ����д�������tag
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
	auto DisableCollision = CallFunc::create([this]() {this->sprite->getPhysicsBody()->setCollisionBitmask(0b0000); });//��������ײ����ֹ��ģʱ���ֵ�����
	auto jump = MoveBy::create(0.5, Vec2(0, this->sprite->getContentSize().height * 2.6f));
	auto EnableCollision = CallFunc::create([this]() {this->sprite->getPhysicsBody()->setCollisionBitmask(0b0010); });//�ָ�ԭ�е�CollisionBitmask
	this->sprite->runAction(Spawn::create(DisableCollision, jump, EnableCollision, dodgeMove, nullptr));
}

void doubleAIcontrol(const Vec2& posOfPlayer, Monster* ai1, Monster* ai2, float dt, Scene* scene)
{
	/*
	*��ʼ��ʱ��ʱ����1����λ������2�ǽ��������ҽ����������֥ʿ
	*/
	static Monster* monsterFirst = ai1;
	static Monster* monsterSecond = ai2;

	Vec2 posOfMonster1 = monsterFirst->sprite->getPosition();//��ȡ��ʱ����1λ��
	Vec2 posOfMonster2 = monsterSecond->sprite->getPosition();//��ȡ��ʱ����2λ��
	static float stepTime = 0;
	static float fireTime = 0;
	static int fireTimeNum = 0;
	stepTime += dt;

	/*��ʱ������Ƿ��ڳ���������λ*/
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



	/*���Ƚ��ж���ҵķ��򣬹��ｫ������ҷ���*/

	//����1
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

	//����2
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
		/*�������ͬһ��Ĺ��ｫ������ҷ���ˮƽ�ƶ�*/
		if (fabs(posOfMonster1.y - posOfPlayer.y) < 20)
		{
			/*������λ������ҵ��ұ�ʱ����ʱ���ｫ�������ƶ�*/
			if ((posOfMonster1.x - posOfPlayer.x) > 150)
			{
				Vec2 rePosition(-64, 0);
				auto moveBy = MoveBy::create(0.5f, rePosition);
				monsterFirst->sprite->runAction(moveBy);
			}
			/*������λ������ҵ����ʱ����ʱ���ｫ�������ƶ�*/
			else if (((posOfPlayer.x - posOfMonster1.x) > 150))
			{
				Vec2 rePosition(64, 0);
				auto moveBy = MoveBy::create(0.5f, rePosition);
				monsterFirst->sprite->runAction(moveBy);
			}
		}

		if (fabs(posOfMonster2.y - posOfPlayer.y) < 20)
		{
			/*������λ������ҵ��ұ�ʱ����ʱ���ｫ�������ƶ�*/
			if ((posOfMonster2.x - posOfPlayer.x) > 150)
			{
				Vec2 rePosition(-64, 0);
				auto moveBy = MoveBy::create(0.5f, rePosition);
				monsterSecond->sprite->runAction(moveBy);
			}
			/*������λ������ҵ����ʱ����ʱ���ｫ�������ƶ�*/
			else if (((posOfPlayer.x - posOfMonster2.x) > 150))
			{
				Vec2 rePosition(64, 0);
				auto moveBy = MoveBy::create(0.5f, rePosition);
				monsterSecond->sprite->runAction(moveBy);
			}
		}



		/*��ʱ������ڽ���״̬ʱ����AI���ܿ���������ҵı�����й���*/
		if (posOfMonster1.x <= posOfPlayer.x && posOfMonster2.x > 0 && posOfMonster2.x < 1300 && posOfMonster2.x <= posOfPlayer.x && fabs(posOfMonster2.y - posOfPlayer.y) < 20)
		{
			if (posOfPlayer.x < 900)
			{
				/*��ʱ��AI���Խ�����Ծ�������õ������±߽������*/
				float distance = posOfPlayer.x - posOfMonster2.x;

				auto moveX1 = MoveBy::create(0.5, Vec2(140, 0));
				auto movejump = MoveBy::create(0.5, Vec2(0, monsterSecond->sprite->getContentSize().height * 2.6f));

				if (distance > 100)
				{
					/*��ʱAI���Կ��ǲ��ܽ���ֻ������Ծ������Ҫ����ˮƽ�ƶ�*/
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
				/*��ʱ��AI���Խ�����Ծ�������õ������±߽������*/
				float distance = posOfMonster2.x - posOfPlayer.x;

				auto moveX1 = MoveBy::create(0.5, Vec2(-140, 0));
				auto movejump = MoveBy::create(0.5, Vec2(0, monsterSecond->sprite->getContentSize().height * 2.6f));

				if (distance > 100)
				{
					/*��ʱAI���Կ��ǲ��ܽ���ֻ������Ծ������Ҫ����ˮƽ�ƶ�*/
					auto moveX2 = MoveBy::create(0.5, Vec2(100 - distance, 0));
					monsterSecond->sprite->runAction(Sequence::create(Spawn::create(moveX1, movejump, nullptr), moveX2, nullptr));
				}
				else
					monsterSecond->sprite->runAction(Spawn::create(moveX1, movejump, nullptr));
			}
		}

		if (posOfPlayer.y - posOfMonster1.y > monsterFirst->sprite->getContentSize().height && posOfPlayer.y < 880)
		{
			/*��ʱ�����AI�Ƿ��ڱ߽磬�޷���������ʱ������б�����ķ�ʽ����*/
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

			/*��ʱAI��ִ������*/
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
			/*��ʱ�����AI�Ƿ��ڱ߽磬�޷���������ʱ������б�����ķ�ʽ����*/
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

			/*��ʱAI��ִ������*/
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

	/*****************************ÿ��0.88�룬���ｫˢ��һ�Σ�����Ƿ���Ҫ���**************************************/
	if ((fireTime > 0.6f && fireTimeNum != 0) || (fireTimeNum == 0 && fireTime > 3.f))
	{
		/*��ʱ��������ص��������*/

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
