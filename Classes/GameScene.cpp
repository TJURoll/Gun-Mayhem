#include"GameScene.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = GameScene::create();
	scene->initWithPhysics();
	//	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, -800.f));//设置了重力为800像素每秒的平方
	return scene;
}
void GameScene::timeUpdate(float ft)
{
	Time* clock = dynamic_cast<Time*>(this->getChildByName("clock"));
	clock->timeUpdate();

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

	//音乐引擎
	auto instance = CocosDenshion::SimpleAudioEngine::getInstance();
	auto volume = instance->getBackgroundMusicVolume();
	instance->stopBackgroundMusic(); //stop后无法恢复播放
	instance->playBackgroundMusic("Music/Game.mp3", true);
	instance->setBackgroundMusicVolume(volume);

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


	//时间显示
	auto time = Time::create();
	time->addClock(this);
	this->schedule(CC_SCHEDULE_SELECTOR(GameScene::timeUpdate), 1.f);


	/**************************************创建平台物理效果*******************************************************/
	{
		float transformX = contentSize.width / 300.f;
		float transformY = contentSize.height / 176.f;
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
		auto body = PhysicsBody::createEdgeBox(visibleSize * 1.5, PHYSICSBODY_MATERIAL_DEFAULT, 20.0f);
		auto edgeNode = Node::create();
		edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		edgeNode->setPhysicsBody(body);
		this->addChild(edgeNode);
		setGroundBitMasks(edgeNode);
	}

	/*********************************************初始化玩家控制角色*******************************************************/
	hero1.sprite->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height + hero1.sprite->getContentSize().height);
	auto bodyplayer = PhysicsBody::createBox(hero1.sprite->getContentSize(), PhysicsMaterial(1.f, 0.f, .8f));//密度、恢复系数、摩擦
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

	/*********************************************初始化AI怪物01角色*******************************************************/
	monster1.sprite->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height + hero1.sprite->getContentSize().height);
	auto bodymonster1 = PhysicsBody::createBox(monster1.sprite->getContentSize(), PhysicsMaterial(1.f, 0.f, .8f));
	bodymonster1->setRotationEnable(false);
	bodymonster1->setCategoryBitmask(0b1111);
	bodymonster1->setCollisionBitmask(0b0010);
	bodymonster1->setContactTestBitmask(0b0010);//敌方角色的掩码
	bodymonster1->setMass(MASS);
	monster1.sprite->setPhysicsBody(bodymonster1);
	monster1.sprite->setTag(10);//第一个怪物标签设为10
	this->addChild(monster1.sprite);


	/*********************************************初始化AI怪物02角色*******************************************************/
	if (g_NumOfAI == 2)
	{
		monster2.sprite->setPosition(origin.x + visibleSize.width / 2 - 100, origin.y + visibleSize.height + hero1.sprite->getContentSize().height);
		auto bodymonster2 = PhysicsBody::createBox(monster2.sprite->getContentSize(), PhysicsMaterial(1.f, 0.f, .8f));
		bodymonster2->setRotationEnable(false);
		bodymonster2->setCategoryBitmask(0b1111);
		bodymonster2->setCollisionBitmask(0b0011);
		bodymonster2->setContactTestBitmask(0b0011);//敌方角色的掩码
		bodymonster2->setMass(MASS);
		monster2.sprite->setPhysicsBody(bodymonster2);
		monster2.sprite->setTag(11);//第二个怪物标签设为11
		this->addChild(monster2.sprite);
	}

	/*********************************************玩家初始枪械*******************************************************/
	Gun* initGun = HandGun::create();
	initGun->bindShooter(hero1.sprite);

	/********************************************AI怪物01初始枪械*******************************************************/
	Gun* initMonsterGun = MachineGun::create();
	initMonsterGun->bindShooter(monster1.sprite);

	/********************************************AI怪物02初始枪械*******************************************************/
	if (g_NumOfAI == 2)
	{
		Gun* initMonster2Gun = MachineGun::create();
		initMonster2Gun->bindShooter(monster2.sprite);
	}

	/*********************************************掉落武器***********************************************************/
	dropWeapons();

	/*********************************************监视器创建*********************************************************/
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
	_mouseListener = EventListenerMouse::create();//鼠标监视器直接作为了GameScene成员
	_mouseListener->onMouseDown = [=](Event* event) {
		EventMouse* mouse = dynamic_cast<EventMouse*>(event);
		switch (mouse->getMouseButton())
		{
		case EventMouse::MouseButton::BUTTON_LEFT:
			CCLOG("press");
			dynamic_cast<Gun*>(hero1.sprite->getChildByName("gun"))->fire(this, &hero1);//寻找到角色之中名为gun的child，转为Gun类型
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

	/*创建碰撞监视器*/
	//1.刷新跳跃次数的碰撞监听器
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
	//2.检测道具碰撞相关的监听器
	addContactListener();//监听器直接加在了场景之上

	//生命系统可视化
	auto Vitality = Sprite::create("vitality.png");
	Label* label;
	if (!g_InfiniteLives)
		label = Label::createWithTTF("5", "fonts/Marker Felt.ttf", 32);
	else
		label = Label::createWithTTF("Infinite", "fonts/Marker Felt.ttf", 32);
	label->setTag(-10);
	Vitality->setPosition(Vec2(Vitality->getContentSize().width / 2, visibleSize.height - Vitality->getContentSize().height));
	label->setPosition(Vec2(Vitality->getContentSize().width + label->getContentSize().width, visibleSize.height - Vitality->getContentSize().height));
	this->addChild(label);
	this->addChild(Vitality);

	//更新函数
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
		auto DisableCollision = CallFunc::create([this]() {hero1.sprite->getPhysicsBody()->setCollisionBitmask(0b0000); });//不允许碰撞，防止穿模时出现的问题
		auto jump = MoveBy::create(0.5f, Vec2(0, hero1.sprite->getContentSize().height * 3.f));
		auto EnableCollision = CallFunc::create([this]() {hero1.sprite->getPhysicsBody()->setCollisionBitmask(0b0100); });//恢复原有的CollisionBitmask
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
	// 初始化了随机数生成器
	srand((unsigned int)time(nullptr));
	// 每隔20秒生成一个宝箱
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
	int minX = static_cast<int>(boxContentSize.width * 2);
	int maxX = static_cast<int>(sceneSize.width - minX);
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
	hero1.sprite->runAction(RotateTo::create(0.1f, 0));


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

	if (!g_InfiniteLives)
	{
		std::string Life = ":";
		char Num = (hero1.getlifeNum() + '0');
		Life += Num;
		auto label = getChildByTag(-10);
		static_cast<Label*>(label)->setString(Life);
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	if (hero1.sprite->getPositionY() < 0)
	{
		hero1.sprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height + hero1.sprite->getContentSize().height));//回到初始位置
		hero1.sprite->getPhysicsBody()->setVelocity(Vec2(0, 0));
		if (!g_InfiniteLives)
			hero1.setlifeNum(hero1.getlifeNum() - 1);
	}
	if (monster1.getlifeNum() != 0 && monster1.sprite->getPositionY() < 0)
	{
		monster1.sprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height + monster1.sprite->getContentSize().height));//回到初始位置
		monster1.sprite->getPhysicsBody()->setVelocity(Vec2(0, 0));
		monster1.setlifeNum(monster1.getlifeNum() - 1);
	}

	if (g_NumOfAI == 2)
	{
		if (monster2.getlifeNum() != 0 && monster2.sprite->getPositionY() < 0)
		{
			monster2.sprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height + monster2.sprite->getContentSize().height));//回到初始位置
			monster2.sprite->getPhysicsBody()->setVelocity(Vec2(0, 0));
			monster2.setlifeNum(monster2.getlifeNum() - 1);
		}
	}

	if (hero1.getlifeNum() == 0)//当玩家的命为0时结束游戏
	{
		g_Win = false;
		Director::getInstance()->replaceScene(ResultScene::createScene());//切换场景
	}
	if (g_NumOfAI == 1)
	{
		if (monster1.getlifeNum() == 0)
		{
			output();
			g_Win = true;
			Director::getInstance()->replaceScene(ResultScene::createScene());//切换场景
		}
		this->monster1.AIUpdate(dt, hero1.sprite->getPosition(), this);
	}
	else
	{
		Monster* ai1 = &monster1;
		Monster* ai2 = &monster2;

		if (monster1.getlifeNum() == 0)//当玩家的命为0时结束游戏
		{
			this->removeChild(monster1.sprite);
			ai1 = nullptr;
		}
		if (monster2.getlifeNum() == 0)//当玩家的命为0时结束游戏
		{
			this->removeChild(monster2.sprite);
			ai2 = nullptr;
		}
		if (monster1.getlifeNum() == 0 && monster2.getlifeNum() == 0)
		{
			output();
			g_Win = true;
			Director::getInstance()->replaceScene(ResultScene::createScene());//切换场景
		}

		/*此时采取单独的一个双控制函数，避免延时过于严重的问题*/
		doubleAIcontrol(hero1.sprite->getPosition(), dt, this, ai1, ai2);
	}
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

					if (node[!i]->getTag() > 0 && node[!i]->getTag() / 20 == 0)
					{
						score += 1;
						auto label = Label::createWithTTF("HIT", "fonts/Marker Felt.ttf", 60);
						label->setScaleX(1.5f);
						label->setTextColor(Color4B(255, 80, 60, 180));
						label->setPosition(Vec2(50, 150));
						node[i]->addChild(label);
						auto impulse = 30 * MASS * (node[!i]->getPosition().x - node[i]->getPosition().x < 0 ? -firePower : firePower);
						if (rand() % 10 == 0)
						{
							impulse *= 3;
							label->setString("CRIT");
							label->setScaleX(2.0f);
							label->setScaleY(1.5f);
							label->setTextColor(Color4B(255, 0, 0, 180));
						}
						node[!i]->getPhysicsBody()->applyImpulse(Vec2(impulse, 0));
					}
					auto boomEffect = [node, i]() {
						dynamic_cast<Sprite*>(node[i])->setTexture("explodeboom.png");
						node[i]->getPhysicsBody()->setDynamic(false);
					};
					node[i]->runAction(Sequence::create(CallFunc::create(boomEffect), DelayTime::create(.1f), RemoveSelf::create(), nullptr));
					break;
				}
				if (tag[i] == -4)//接触箱子
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

void GameScene::output()
{
	string playerName = "Player1";
	Time* clock = dynamic_cast<Time*>(this->getChildByName("clock"));
	int myTime = int(*clock);//类型转换函数
	if (g_NumOfAI == 2)
		score += 50;
	if (myTime < 200)
		score += 100 - myTime / 2;
	score += hero1.getlifeNum() * 10;
	auto fileUtiles = FileUtils::getInstance();
	string filePath = fileUtiles->fullPathForFilename("score.txt");
	ofstream outfile;
	outfile.open(filePath, ios::app);
	outfile << playerName << ' ' << clock->timeShow() << ' ' << score << endl;
	outfile.close();
}
