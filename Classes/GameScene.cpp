#include"GameScene.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = GameScene::create();
	scene->initWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, -490.f));//设置了重力为490像素每秒的平方
	return scene;
}

bool GameScene::init()
{
	//检测初始化是否成功
	if (!Scene::init())
	{
		return false;
	}
	//初始化可视边界以及原点
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//创建背景地图
	auto bg = Sprite::create("mpbg.png");
	auto contentSize = bg->getContentSize();
	float sizeTransform_x = visibleSize.width / contentSize.width;
	float sizeTransform_y = visibleSize.height / contentSize.height;
	bg->setScale(sizeTransform_x, sizeTransform_y);
	bg->setAnchorPoint(Vec2(0.5, 0.5));
	Size sizeOfbg = bg->getContentSize();
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg);


	//创建平台物理效果
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
		// 创建边界物理接触
		auto body = PhysicsBody::createEdgeBox(visibleSize*1.5, PHYSICSBODY_MATERIAL_DEFAULT,20.0f);
		auto edgeNode = Node::create();
		edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		edgeNode->setPhysicsBody(body);
		this->addChild(edgeNode);
		setGroundBitMasks(edgeNode);
	}

	//初始化玩家控制角色
	hero1.sprite->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - hero1.sprite->getContentSize().height);
	auto bodyplayer = PhysicsBody::createBox(hero1.sprite->getContentSize(), PhysicsMaterial(1.f,0.f,1.f));//密度、恢复系数、摩擦
	bodyplayer->setRotationEnable(false);//不可转动
	bodyplayer->setCategoryBitmask(0b1111);
	bodyplayer->setCollisionBitmask(0b0100);
	bodyplayer->setContactTestBitmask(0b0100);//我方角色的掩码
	//bodyplayer->setCategoryBitmask(0b1111);
	//bodyplayer->setCollisionBitmask(0b0010);
	//bodyplayer->setContactTestBitmask(0b0010);//敌方角色的掩码
	bodyplayer->setMass(MASS);//设置质量
	hero1.sprite->setPhysicsBody(bodyplayer);
	hero1.sprite->setTag(0);//玩家标签设为0
	this->addChild(hero1.sprite);

	Gun* initGun = HandGun::create();
	initGun->bindShooter(hero1.sprite);
	addContactListener();

	dropWeapons();
	/*以下创建监视器部分取自官方文档以及CSDN*/
	/*创建键盘监视器*/
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	listener->onKeyReleased = [&](EventKeyboard::KeyCode keycode, Event* event)
	{
		KeyMap[keycode] = false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	/*创建鼠标监视器*/
	 _mouseListener = EventListenerMouse::create();
	//_mouseListener->onMouseMove = CC_CALLBACK_1(StartScene::onMouseMove, this);
	//_mouseListener->onMouseUp = CC_CALLBACK_1(StartScene::onMouseUp, this);
	_mouseListener->onMouseDown = [=](Event* event) {
		EventMouse* mouse = dynamic_cast<EventMouse*>(event);
		switch (mouse->getMouseButton())
		{
		case EventMouse::MouseButton::BUTTON_LEFT:
			CCLOG("press");
			dynamic_cast<Gun*>(hero1.sprite->getChildByName("gun"))->fire(this, &hero1);
			dynamic_cast<Gun*>(hero1.sprite->getChildByName("gun"))->stopAWhile(_mouseListener);
			break;
		case EventMouse::MouseButton::BUTTON_RIGHT:
			dynamic_cast<Gun*>(hero1.sprite->getChildByName("gun"))->throwExplosives(this, &hero1);
			break;
		default:
			break;
		};
	};
	//_mouseListener->onMouseScroll = CC_CALLBACK_1(StartScene::onMouseScroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);


	//更新函数
	this->scheduleUpdate();
	return true;
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)
{
	KeyMap[keycode] = true;

	auto Jump = JumpBy::create(1, Vec2(0, 80), 80, 1);
	if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_SPACE || keycode == cocos2d::EventKeyboard::KeyCode::KEY_W)
		hero1.sprite->runAction(MoveBy::create(0.5, Vec2(0, hero1.sprite->getContentSize().height * 2.8)));
	if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_S)
		hero1.sprite->runAction(MoveBy::create(0.5, Vec2(0, -hero1.sprite->getContentSize().height*2 )));
}

void GameScene::dropWeapons()
{
	// 初始化了随机数生成器
	srand((unsigned int)time(nullptr));
	// 每隔20秒生成一个宝箱
	this->schedule(CC_SCHEDULE_SELECTOR(GameScene::addBoxes), 20.f);
}
void GameScene::setGroundBitMasks(Node* node)
{
	auto physicsBody=node->getPhysicsBody();
	physicsBody->setCategoryBitmask(0b1111);
	physicsBody->setCollisionBitmask(0b1111);
	physicsBody->setContactTestBitmask(0b11001);
	node->setTag(100);
}
void GameScene::addBoxes(float ft)
{
	auto box = Sprite::create("box.png");
	auto boxContentSize = box->getContentSize();
	auto sceneSize = this->getContentSize();
	int minX = boxContentSize.width * 2;
	int maxX = sceneSize.width - minX;
	int rangeX = maxX - minX;
	int randomX = (rand() % rangeX) + minX;
    box->setPosition(Vec2(randomX, sceneSize.height));//X坐标随机,Y坐标为顶
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
	//旋转人物精灵
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
		/*如果先前英雄向右方向，并且按下了A，松开了D，则改变方向*/
		this->hero1.changeTexture(true);//图像翻转

		this->hero1.changeDirection(true);//储存数据翻转
	}

	if (KeyMap[cocos2d::EventKeyboard::KeyCode::KEY_D] == true && KeyMap[cocos2d::EventKeyboard::KeyCode::KEY_A] == false && this->hero1.getDirection() == true)
	{
		/*如果先前英雄向左方向，并且按下了D，松开了A，则改变方向*/
		this->hero1.changeTexture(false);//图像翻转

		this->hero1.changeDirection(false);//储存数据翻转
	}

	Vec2 rePosition(moveX, 0);
	auto moveBy = MoveBy::create(0.5f, rePosition);
	hero1.sprite->runAction(moveBy);
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
				if (tag[i] == -2)//正在爆炸的炸药
				{
					node[!i]->getPhysicsBody()->applyImpulse(Vec2((node[!i]->getPosition().x - node[i]->getPosition().x < 0 ? -400 : 400) * MASS, 100 * MASS));
					break;
				}
				if (tag[i] == -3)//子弹
				{
					int firePower = static_cast<int>((node[i]->getName())[0]);
					node[!i]->getPhysicsBody()->applyImpulse(Vec2(30 * MASS * (node[!i]->getPosition().x - node[i]->getPosition().x < 0 ? -firePower : firePower), 0));
					auto boomEffect = [node, i]() {
						dynamic_cast<Sprite*>(node[i])->setTexture("explodeboom.png");
						node[i]->getPhysicsBody()->setDynamic(false);
					};
					node[i]->runAction(Sequence::create(CallFunc::create(boomEffect), DelayTime::create(.1f), RemoveSelf::create(), nullptr));
					break;
				}
				if (tag[i] == -4)
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