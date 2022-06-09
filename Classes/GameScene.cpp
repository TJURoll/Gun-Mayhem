#include"GameScene.h"
#include"PauseScene.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = GameScene::create();
	scene->initWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, -800.f));//����������Ϊ800����ÿ���ƽ��
	return scene;
}

bool GameScene::init()
{
	//����ʼ���Ƿ�ɹ�
	if (!Scene::init())
	{
		return false;
	}
	//��ʼ�����ӱ߽��Լ�ԭ��
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//��������
	auto instance = CocosDenshion::SimpleAudioEngine::getInstance();
	auto volume = instance->getBackgroundMusicVolume();
	instance->stopBackgroundMusic(); //stop���޷��ָ�����
		instance->playBackgroundMusic("Music/Game.mp3", true);
	instance->setBackgroundMusicVolume(volume);

	//����������ͼ
	auto bg = Sprite::create("mpbg.png");
	auto contentSize = bg->getContentSize();
	float sizeTransform_x = visibleSize.width / contentSize.width;
	float sizeTransform_y = visibleSize.height / contentSize.height;
	bg->setScale(sizeTransform_x, sizeTransform_y);
	bg->setAnchorPoint(Vec2(0.5, 0.5));
	Size sizeOfbg = bg->getContentSize();
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg);


	/**************************************����ƽ̨����Ч��*******************************************************/
	{
		float transformX = contentSize.width / 300.0;
		float transformY = contentSize.height / 176.0;
		Size bodySize1 = cocos2d::Size((122 - 54) * transformX * sizeTransform_x, 1);
		auto bodyPlatform1 = PhysicsBody::createEdgeBox(bodySize1);
		auto Platform1 = Node::create();
		Platform1->setPosition(Vec2((122 + 54) / 2 * transformX * sizeTransform_x, (176 - 50) * transformY * sizeTransform_y));
		Platform1->setPhysicsBody(bodyPlatform1);
		this->addChild(Platform1);
		setGroundBitMasks(Platform1);

		Size bodySize2 = cocos2d::Size((159 - 42) * transformX * sizeTransform_x, 1);
		auto bodyPlatform2 = PhysicsBody::createEdgeBox(bodySize2);
		auto Platform2 = Node::create();
		Platform2->setPosition(Vec2((159 + 42) / 2 * transformX * sizeTransform_x, (176 - 78) * transformY * sizeTransform_y));
		Platform2->setPhysicsBody(bodyPlatform2);
		this->addChild(Platform2);
		setGroundBitMasks(Platform2);

		Size bodySize3 = cocos2d::Size((213 - 37) * transformX * sizeTransform_x, 1);
		auto bodyPlatform3 = PhysicsBody::createEdgeBox(bodySize3);
		auto Platform3 = Node::create();
		Platform3->setPosition(Vec2((213 + 37) / 2 * transformX * sizeTransform_x, (176 - 105) * transformY * sizeTransform_y));
		Platform3->setPhysicsBody(bodyPlatform3);
		this->addChild(Platform3);
		setGroundBitMasks(Platform3);

		Size bodySize4 = cocos2d::Size((246 - 29) * transformX * sizeTransform_x, 1);
		auto bodyPlatform4 = PhysicsBody::createEdgeBox(bodySize4);
		auto Platform4 = Node::create();
		Platform4->setPosition(Vec2((246 + 26) / 2 * transformX * sizeTransform_x, (176 - 132) * transformY * sizeTransform_y));
		Platform4->setPhysicsBody(bodyPlatform4);
		this->addChild(Platform4);
		setGroundBitMasks(Platform4);

		Size bodySize5 = cocos2d::Size((289 - 18) * transformX * sizeTransform_x, 1);
		auto bodyPlatform5 = PhysicsBody::createEdgeBox(bodySize5);
		auto Platform5 = Node::create();
		Platform5->setPosition(Vec2((289 + 18) / 2 * transformX * sizeTransform_x, (176 - 162) * transformY * sizeTransform_y));
		Platform5->setPhysicsBody(bodyPlatform5);
		this->addChild(Platform5);
		setGroundBitMasks(Platform5);
	}

	{
		// �����߽�����Ӵ�
		auto body = PhysicsBody::createEdgeBox(visibleSize * 1.5, PHYSICSBODY_MATERIAL_DEFAULT, 20.0f);
		auto edgeNode = Node::create();
		edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		edgeNode->setPhysicsBody(body);
		this->addChild(edgeNode);
		setGroundBitMasks(edgeNode);
	}

	/*********************************************��ʼ����ҿ��ƽ�ɫ*******************************************************/
	hero1.sprite->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height + hero1.sprite->getContentSize().height);
	auto bodyplayer = PhysicsBody::createBox(hero1.sprite->getContentSize(), PhysicsMaterial(1.f, 0.f, .8f));//�ܶȡ��ָ�ϵ����Ħ��
	bodyplayer->setRotationEnable(false);//����ת��
	bodyplayer->setCategoryBitmask(0b1111);
	bodyplayer->setCollisionBitmask(0b0100);
	bodyplayer->setContactTestBitmask(0b0100);//�ҷ���ɫ������
	//bodyplayer->setCategoryBitmask(0b1111);
	//bodyplayer->setCollisionBitmask(0b0010);
	//bodyplayer->setContactTestBitmask(0b0010);//�з���ɫ������
	bodyplayer->setMass(MASS);//��������
	hero1.sprite->setPhysicsBody(bodyplayer);
	hero1.sprite->setTag(0);//��ұ�ǩ��Ϊ0
	this->addChild(hero1.sprite);

	/*********************************************��ʼ��AI����01��ɫ*******************************************************/
	monster1.sprite->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height + hero1.sprite->getContentSize().height);
	auto bodymonster1 = PhysicsBody::createBox(monster1.sprite->getContentSize(), PhysicsMaterial(1.f, 0.f, .8f));
	bodymonster1->setRotationEnable(false);
	bodymonster1->setCategoryBitmask(0b1111);
	bodymonster1->setCollisionBitmask(0b0010);
	bodymonster1->setContactTestBitmask(0b0010);//�з���ɫ������
	bodymonster1->setMass(MASS);
	monster1.sprite->setPhysicsBody(bodymonster1);
	monster1.sprite->setTag(10);//��һ�������ǩ��Ϊ10
	this->addChild(monster1.sprite);


	/*********************************************��ҳ�ʼǹе*******************************************************/
	Gun* initGun = HandGun::create();
	initGun->bindShooter(hero1.sprite);

	/********************************************AI����01��ʼǹе*******************************************************/
	Gun* initMonsterGun = MachineGun::create();
	initMonsterGun->bindShooter(monster1.sprite);

	/*********************************************��������***********************************************************/
	dropWeapons();

	/*********************************************����������*********************************************************/
	/*���´�������������ȡ�Թٷ��ĵ��Լ�CSDN*/
	/*�������̼�����*/
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	listener->onKeyReleased = [&](EventKeyboard::KeyCode keycode, Event* event)
	{
		KeyMap[keycode] = false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	/*������������*/
	_mouseListener = EventListenerMouse::create();//��������ֱ����Ϊ��GameScene��Ա
	_mouseListener->onMouseDown = [=](Event* event) {
		EventMouse* mouse = dynamic_cast<EventMouse*>(event);
		switch (mouse->getMouseButton())
		{
		case EventMouse::MouseButton::BUTTON_LEFT:
			CCLOG("press");
			dynamic_cast<Gun*>(hero1.sprite->getChildByName("gun"))->fire(this, &hero1);//Ѱ�ҵ���ɫ֮����Ϊgun��child��תΪGun����
			dynamic_cast<Gun*>(hero1.sprite->getChildByName("gun"))->stopAWhile(_mouseListener);
			break;
		case EventMouse::MouseButton::BUTTON_RIGHT:
			dynamic_cast<Gun*>(hero1.sprite->getChildByName("gun"))->throwExplosives(this, &hero1);
			break;
		default:
			break;
		};
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

	/*������ײ������*/
	//1.ˢ����Ծ��������ײ������
	auto listenerPhysics = EventListenerPhysicsContact::create();
	listenerPhysics->onContactBegin = [this](PhysicsContact& contact)
	{
		Node* node[2] = { contact.getShapeA()->getBody()->getNode() ,contact.getShapeB()->getBody()->getNode() };
		if (node[0] && node[1])
		{
			int tag[2] = { node[0]->getTag(),node[1]->getTag() };
			for (int i = 0; i < 2; i++)
				if (tag[i] == 0 && tag[!i] == 100)
					hero1.setJumpTimes(2);
		}

		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerPhysics, this);
	//2.��������ײ��صļ�����
	addContactListener();//������ֱ�Ӽ����˳���֮��

   //���º���
	this->scheduleUpdate();
	return true;
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)
{
	KeyMap[keycode] = true;

	//	auto Jump = JumpBy::create(1, Vec2(0, 80), 80, 1);

	if ((keycode == cocos2d::EventKeyboard::KeyCode::KEY_SPACE || keycode == cocos2d::EventKeyboard::KeyCode::KEY_W)
		&& hero1.getJumpTimes() > 0)
	{
		auto DisableCollision = CallFunc::create([this]() {hero1.sprite->getPhysicsBody()->setCollisionBitmask(0b0000); });//��������ײ����ֹ��ģʱ���ֵ�����
		auto jump = MoveBy::create(0.5, Vec2(0, hero1.sprite->getContentSize().height * 3.0));
		auto EnableCollision = CallFunc::create([this]() {hero1.sprite->getPhysicsBody()->setCollisionBitmask(0b0100); });//�ָ�ԭ�е�CollisionBitmask
		hero1.sprite->runAction(Sequence::create(DisableCollision, jump, EnableCollision, nullptr));
		hero1.setJumpTimes(hero1.getJumpTimes() - 1);
	}
	if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_S)
		hero1.sprite->runAction(MoveBy::create(0.5, Vec2(0, -hero1.sprite->getContentSize().height * 2)));
	if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_P)
		Director::getInstance()->pushScene(PauseScene::createScene());
}

void GameScene::dropWeapons()
{
	// ��ʼ���������������
	srand((unsigned int)time(nullptr));
	// ÿ��20������һ������
	this->schedule(CC_SCHEDULE_SELECTOR(GameScene::addBoxes), 20.f);
}
void GameScene::setGroundBitMasks(Node* node)
{
	auto physicsBody = node->getPhysicsBody();
	physicsBody->setCategoryBitmask(0b1111);
	physicsBody->setCollisionBitmask(0b1111);
	physicsBody->setContactTestBitmask(0b11001);
	node->setTag(100);
}
void GameScene::addBoxes(const float ft)
{
	auto box = Sprite::create("box.png");
	auto boxContentSize = box->getContentSize();
	auto sceneSize = this->getContentSize();
	int minX = boxContentSize.width * 2;
	int maxX = sceneSize.width - minX;
	int rangeX = maxX - minX;
	int randomX = (rand() % rangeX) + minX;
	box->setPosition(Vec2(randomX, sceneSize.height));//X�������,Y����Ϊ��
	auto physicsBody = PhysicsBody::createBox(box->getContentSize(), PhysicsMaterial(10000.f, 0.f, 1.f));
	physicsBody->setCategoryBitmask(0b0110);
	physicsBody->setCollisionBitmask(0b1001);
	physicsBody->setContactTestBitmask(0b1001);
	physicsBody->setRotationEnable(false);
	box->setPhysicsBody(physicsBody);
	box->setTag(-4);
	this->addChild(box);
}


void GameScene::update(float dt)
{
	//��ת���ﾫ��
	hero1.sprite->runAction(RotateTo::create(0.1, 0));


	float moveX(0);
	auto left = EventKeyboard::KeyCode::KEY_A;
	auto right = EventKeyboard::KeyCode::KEY_D;
	if (KeyMap[left])
	{
		moveX = -4;
	}
	else if (KeyMap[right])
	{
		moveX = 4;
	}

	if (KeyMap[cocos2d::EventKeyboard::KeyCode::KEY_D] == false && KeyMap[cocos2d::EventKeyboard::KeyCode::KEY_A] == true && this->hero1.getDirection() == false)
	{
		/*�����ǰӢ�����ҷ��򣬲��Ұ�����A���ɿ���D����ı䷽��*/
		this->hero1.changeTexture(true);//ͼ��ת

		this->hero1.changeDirection(true);//�������ݷ�ת
	}

	if (KeyMap[cocos2d::EventKeyboard::KeyCode::KEY_D] == true && KeyMap[cocos2d::EventKeyboard::KeyCode::KEY_A] == false && this->hero1.getDirection() == true)
	{
		/*�����ǰӢ�������򣬲��Ұ�����D���ɿ���A����ı䷽��*/
		this->hero1.changeTexture(false);//ͼ��ת

		this->hero1.changeDirection(false);//�������ݷ�ת
	}

	Vec2 rePosition(moveX, 0);
	auto moveBy = MoveBy::create(0.5f, rePosition);
	hero1.sprite->runAction(moveBy);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	if (hero1.sprite->getPositionY() < 0)
	{
		hero1.sprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height + hero1.sprite->getContentSize().height));//�ص���ʼλ��
		hero1.sprite->getPhysicsBody()->setVelocity(Vec2(0, 0));
		hero1.setlifeNum(hero1.getlifeNum() - 1);
	}
	if (monster1.sprite->getPositionY() < 0)
	{
		monster1.sprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height + monster1.sprite->getContentSize().height));//�ص���ʼλ��
		monster1.sprite->getPhysicsBody()->setVelocity(Vec2(0, 0));
		monster1.setlifeNum(monster1.getlifeNum() - 1);
	}
	if (hero1.getlifeNum() == 0)//����ҵ���Ϊ0ʱ������Ϸ
	{
		;//�л�����
	}

	this->monster1.AIUpdate(dt, hero1.sprite->getPosition(),this);
}
void GameScene::addContactListener()
{
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [this](PhysicsContact& contact) {
		Node* node[2] = { contact.getShapeA()->getBody()->getNode() ,contact.getShapeB()->getBody()->getNode() };
		if (node[0] && node[1])
		{
			int tag[2] = { node[0]->getTag(),node[1]->getTag() };
			for (int i = 0; i < 2; i++)
			{
				if (tag[i] == -2)//���ڱ�ը��ըҩ
				{
					node[!i]->getPhysicsBody()->applyImpulse(Vec2((node[!i]->getPosition().x - node[i]->getPosition().x < 0 ? -400 : 400) * MASS, 100 * MASS));
					break;
				}
				if (tag[i] == -3)//�ӵ�
				{
					int firePower = static_cast<int>((node[i]->getName())[0]);
					auto impulse = 30 * MASS * (node[!i]->getPosition().x - node[i]->getPosition().x < 0 ? -firePower : firePower);
					CCLOG("%f", impulse);
					node[!i]->getPhysicsBody()->applyImpulse(Vec2(impulse, 0));
					auto boomEffect = [node, i]() {
						dynamic_cast<Sprite*>(node[i])->setTexture("explodeboom.png");
						node[i]->getPhysicsBody()->setDynamic(false);
					};
					node[i]->runAction(Sequence::create(CallFunc::create(boomEffect), DelayTime::create(.1f), RemoveSelf::create(), nullptr));
					break;
				}
				if (tag[i] == -4)//�Ӵ�����
				{
					node[!i]->removeAllChildrenWithCleanup(true);
					_mouseListener->setEnabled(true);
					auto gun = randomGun();
					gun->bindShooter(dynamic_cast<Sprite*>(node[!i]));
					if (dynamic_cast<Sprite*>(node[!i])->isFlippedX())
						gun->setFlippedX(true);
					auto smogEffect = [node, i]() {
						dynamic_cast<Sprite*>(node[i])->setTexture("smog.png");
						node[i]->getPhysicsBody()->setDynamic(false);
					};
					auto swell = ScaleTo::create(.2f, 3);
					node[i]->runAction(Sequence::create(CallFunc::create(smogEffect), swell, RemoveSelf::create(), nullptr));
				}
			}

			CCLOG("onContact!!  tagA = %d, tagB = %d", tag[0], tag[1]);
		}
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}
Gun* GameScene::randomGun()
{
	Gun* p = nullptr;
	switch (rand() % 3) {
	case 0:
		p = HandGun::create();
		break;
	case 1:
		p = SniperGun::create();
		break;
	case 2:
		p = MachineGun::create();
	}
	return p;
}


