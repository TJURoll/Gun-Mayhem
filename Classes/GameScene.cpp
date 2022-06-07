#include"GameScene.h"
#include<string>
USING_NS_CC;

#define Platform1_x (122 + 54) / 2
#define Platform1_y (176 - 50)
#define Platform1_width (122 - 54)

#define Platform2_x (159 + 42) / 2
#define Platform2_y (176 - 78)
#define Platform2_width (159 - 42)

#define Platform3_x (213 + 37) / 2
#define Platform3_y (176 - 105)
#define Platform3_width (213 - 37) 

#define Platform4_x (246 + 26) / 2
#define Platform4_y (176 - 132)
#define Platform4_width (246 - 29)

#define Platform5_x (289 + 18) / 2
#define Platform5_y (176 - 162)
#define Platform5_width (289 - 18)

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
	bg->setTag(11);
	this->addChild(bg);

	//**************************************创建平台物理效果*******************************************************//
	{
		float transformX = contentSize.width / 300.0;
		float transformY = contentSize.height / 176.0;

		Size bodySize1 = cocos2d::Size((122 - 54) * transformX * sizeTransform_x, 1);
		auto bodyPlatform1 = PhysicsBody::createEdgeBox(bodySize1);
		//设置碰撞掩码
		bodyPlatform1->setCategoryBitmask(0b0100000);
		bodyPlatform1->setContactTestBitmask(0b1000000);
		bodyPlatform1->setCollisionBitmask(0b0100000);
		auto Platform1 = Node::create();
		Platform1->setPosition(Vec2((122 + 54) / 2 * transformX * sizeTransform_x, (176 - 50) * transformY * sizeTransform_y));
		Platform1->setPhysicsBody(bodyPlatform1);
		this->addChild(Platform1);

		Size bodySize2 = cocos2d::Size((159 - 42) * transformX * sizeTransform_x, 1);
		auto bodyPlatform2 = PhysicsBody::createEdgeBox(bodySize2);
		//设置碰撞掩码
		bodyPlatform2->setCategoryBitmask(0b0010000);
		bodyPlatform2->setContactTestBitmask(0b1000000);
		bodyPlatform2->setCollisionBitmask(0b0010000);
		auto Platform2 = Node::create();
		Platform2->setPosition(Vec2((159 + 42) / 2 * transformX * sizeTransform_x, (176 - 78) * transformY * sizeTransform_y));
		Platform2->setPhysicsBody(bodyPlatform2);
		this->addChild(Platform2);

		Size bodySize3 = cocos2d::Size((213 - 37) * transformX * sizeTransform_x, 1);
		auto bodyPlatform3 = PhysicsBody::createEdgeBox(bodySize3);
		//设置碰撞掩码
		bodyPlatform3->setCategoryBitmask(0b0001000);
		bodyPlatform3->setContactTestBitmask(0b1000000);
		bodyPlatform3->setCollisionBitmask(0b0001000);
		auto Platform3 = Node::create();
		Platform3->setPosition(Vec2((213 + 37) / 2 * transformX * sizeTransform_x, (176 - 105) * transformY * sizeTransform_y));
		Platform3->setPhysicsBody(bodyPlatform3);
		this->addChild(Platform3);

		Size bodySize4 = cocos2d::Size((246 - 29) * transformX * sizeTransform_x, 1);
		auto bodyPlatform4 = PhysicsBody::createEdgeBox(bodySize4);
		//设置碰撞掩码
		bodyPlatform4->setCategoryBitmask(0b0000100);
		bodyPlatform4->setContactTestBitmask(0b1000000);
		bodyPlatform4->setCollisionBitmask(0b0000100);
		auto Platform4 = Node::create();
		Platform4->setPosition(Vec2((246 + 26) / 2 * transformX * sizeTransform_x, (176 - 132) * transformY * sizeTransform_y));
		Platform4->setPhysicsBody(bodyPlatform4);
		this->addChild(Platform4);

		Size bodySize5 = cocos2d::Size((289 - 18) * transformX * sizeTransform_x, 1);
		auto bodyPlatform5 = PhysicsBody::createEdgeBox(bodySize5);
		//设置碰撞掩码
		bodyPlatform5->setCategoryBitmask(0b0000010);
		bodyPlatform5->setContactTestBitmask(0b1000000);
		bodyPlatform5->setCollisionBitmask(0b0000010);
		auto Platform5 = Node::create();
		Platform5->setPosition(Vec2((289 + 18) / 2 * transformX * sizeTransform_x, (176 - 162) * transformY * sizeTransform_y));
		Platform5->setPhysicsBody(bodyPlatform5);
		this->addChild(Platform5);
	}

	/*********************************************初始化玩家控制角色*******************************************************/
	//hero1.hero->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	hero1.sprite->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - hero1.sprite->getContentSize().height);
	auto bodyplayer = PhysicsBody::createBox(hero1.sprite->getContentSize(), PhysicsMaterial(1.f,0.f,1.f));//密度、恢复系数、摩擦
	bodyplayer->setRotationEnable(false);//不可转动
	//设置质量
	bodyplayer->setMass(MASS);
	hero1.sprite->setPhysicsBody(bodyplayer);
	//设置掩码
	bodyplayer->setCategoryBitmask(0b1111111);
	bodyplayer->setCollisionBitmask(0b0111111);
	bodyplayer->setContactTestBitmask(0b0111111);
	//玩家标签设为0，建议友军为1、2、3，敌军为11、12、13
	hero1.sprite->setTag(0);
	this->addChild(hero1.sprite);

	Gun* gun = HandGun::create();
	gun->bindShooter(hero1.sprite);
	gun->addContactListener();

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
	EventListenerMouse* _mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseDown = [=](Event* event) {
		EventMouse* mouse = dynamic_cast<EventMouse*>(event);
		switch (mouse->getMouseButton())
		{
		case EventMouse::MouseButton::BUTTON_LEFT:
			CCLOG("press");
			gun->fire(this, &hero1);
			gun->stopAWhile(_mouseListener);
			break;
		case EventMouse::MouseButton::BUTTON_RIGHT:
			gun->throwExplosives(this, &hero1);
			break;
		default:
			break;
		};
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

	//创建物理事件监听
	auto listenerPhysics = EventListenerPhysicsContact::create();
	listenerPhysics->onContactBegin = [this](PhysicsContact& contant)
	{
		hero1.setJumpTimes(2);
		return true;
	};
	listenerPhysics->onContactPreSolve = [this](PhysicsContact& contant, PhysicsContactPreSolve& solve)
	{
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerPhysics, this);

	//生命系统的可视化
	char Num;
	auto Vitality = Sprite::create("vitality.png");
	auto label = Label::createWithTTF("5", "fonts/Marker Felt.ttf", 32);
	label->setTag(-10);
	Vitality->setPosition(Vec2(Vitality->getContentSize().width/2, visibleSize.height - Vitality->getContentSize().height));
	label->setPosition(Vec2(Vitality->getContentSize().width+label->getContentSize().width, visibleSize.height - Vitality->getContentSize().height));
	this->addChild(label);
	this->addChild(Vitality);



	//更新函数
	this->scheduleUpdate();
	return true;
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)
{
	KeyMap[keycode] = true;

	auto Jump = JumpBy::create(1, Vec2(0, 80), 80, 1);
	if ((keycode == cocos2d::EventKeyboard::KeyCode::KEY_SPACE || keycode == cocos2d::EventKeyboard::KeyCode::KEY_W)
		&& hero1.getJumpTimes() > 0)
	{
		hero1.sprite->runAction(MoveBy::create(0.5, Vec2(0, hero1.sprite->getContentSize().height * 3)));
		hero1.setJumpTimes(hero1.getJumpTimes() - 1);
	}
}


void GameScene::update(float dt)
{
	float moveX(0);
	auto left = EventKeyboard::KeyCode::KEY_A;
	auto right = EventKeyboard::KeyCode::KEY_D;
	if (KeyMap[left])
	{
		moveX = -5;
	}
	else if (KeyMap[right])
	{
		moveX = 5;
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
	
	//掉下平台
	if (hero1.sprite->getPosition().y < 0)
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		hero1.sprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - hero1.sprite->getContentSize().height));
		hero1.setlifeNum(hero1.getlifeNum() - 1);
	}
	if (hero1.getlifeNum() == 0)//当玩家的命为0时结束游戏
	{
		GameScene::onExit();
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto contentSize = this->getChildByTag(11)->getContentSize();
	float sizeTransform_x = visibleSize.width / contentSize.width;
	float sizeTransform_y = visibleSize.height / contentSize.height;
	float transformX = contentSize.width / 300.0;
	float transformY = contentSize.height / 176.0;
	//解决跳跃时和物理引擎碰撞穿模的问题，刷新掩码
	if (hero1.sprite->getPosition().y > Platform1_y * transformY * sizeTransform_y + hero1.sprite->getContentSize().height / 2)
		hero1.sprite->getPhysicsBody()->setCollisionBitmask(0b0111111);
	else if (hero1.sprite->getPosition().y > Platform2_y * transformY * sizeTransform_y + hero1.sprite->getContentSize().height / 2)
		hero1.sprite->getPhysicsBody()->setCollisionBitmask(0b0011111);
	else if (hero1.sprite->getPosition().y > Platform3_y * transformY * sizeTransform_y + hero1.sprite->getContentSize().height / 2)
		hero1.sprite->getPhysicsBody()->setCollisionBitmask(0b0001111);
	else if (hero1.sprite->getPosition().y > Platform4_y * transformY * sizeTransform_y + hero1.sprite->getContentSize().height / 2)
		hero1.sprite->getPhysicsBody()->setCollisionBitmask(0b0000111);
	else if (hero1.sprite->getPosition().y > Platform5_y * transformY * sizeTransform_y + hero1.sprite->getContentSize().height / 2)
		hero1.sprite->getPhysicsBody()->setCollisionBitmask(0b0000011);
	auto listener = EventListenerKeyboard::create();
	//
	listener->onKeyPressed = [&](EventKeyboard::KeyCode keycode, Event* event)
	{
		if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_S)
		{
			hero1.sprite->getPhysicsBody()->setCollisionBitmask(hero1.sprite->getPhysicsBody()->getCollisionBitmask() >> 1);
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//

	std::string Life = ":";
	char Num = (hero1.getlifeNum() + '0');
	Life += Num;
	auto label = getChildByTag(-10);
	static_cast<Label*>(label)->setString(Life);

	hero1.sprite->runAction(moveBy);
}