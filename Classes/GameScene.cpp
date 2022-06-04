#include"GameScene.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = GameScene::create();
	scene->addChild(layer);
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

	//����������ͼ
		auto bg = Sprite::create("mpbg.png");
		auto contentSize = bg->getContentSize();
		float sizeTransform_x = visibleSize.width / contentSize.width;
		float sizeTransform_y = visibleSize.height / contentSize.height;
		bg->setScale(sizeTransform_x, sizeTransform_y);
		bg->setAnchorPoint(Vec2(0.5, 0.5));
		Size sizeOfbg = bg->getContentSize();
		bg->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height / 2));
		this->addChild(bg);
	

	//����ƽ̨����Ч��
	{
		float transformX = contentSize.width / 300.0;
		float transformY = contentSize.height / 176.0;
		Size bodySize1 = cocos2d::Size((122 - 54)*transformX*sizeTransform_x , 1);
		auto bodyPlatform1 = PhysicsBody::createEdgeBox(bodySize1);
		auto Platform1 = Node::create();
		Platform1->setPosition(Vec2((122 + 54) / 2 * transformX * sizeTransform_x, (176 - 50) * transformY* sizeTransform_y));
		Platform1->setPhysicsBody(bodyPlatform1);
		this->addChild(Platform1);

		Size bodySize2 = cocos2d::Size((159 - 42) * transformX * sizeTransform_x, 1);
		auto bodyPlatform2 = PhysicsBody::createEdgeBox(bodySize2);
		auto Platform2 = Node::create();
		Platform2->setPosition(Vec2((159 + 42) / 2 * transformX * sizeTransform_x, (176 - 78) * transformY * sizeTransform_y));
		Platform2->setPhysicsBody(bodyPlatform2);
		this->addChild(Platform2);

		Size bodySize3 = cocos2d::Size((213 - 37) * transformX * sizeTransform_x, 1);
		auto bodyPlatform3 = PhysicsBody::createEdgeBox(bodySize3);
		auto Platform3 = Node::create();
		Platform3->setPosition(Vec2( (213 + 37) / 2 * transformX * sizeTransform_x, (176 - 105) * transformY * sizeTransform_y));
		Platform3->setPhysicsBody(bodyPlatform3);
		this->addChild(Platform3);

		Size bodySize4 = cocos2d::Size((246 - 29) * transformX * sizeTransform_x, 1);
		auto bodyPlatform4 = PhysicsBody::createEdgeBox(bodySize4);
		auto Platform4 = Node::create();
		Platform4->setPosition(Vec2( (246 + 26) / 2 * transformX * sizeTransform_x, (176 - 132) * transformY * sizeTransform_y));
		Platform4->setPhysicsBody(bodyPlatform4);
		this->addChild(Platform4);

		Size bodySize5 = cocos2d::Size((289 - 18) * transformX * sizeTransform_x, 1);
		auto bodyPlatform5 = PhysicsBody::createEdgeBox(bodySize5);
		auto Platform5 = Node::create();
		Platform5->setPosition(Vec2((289 + 18) / 2 * transformX * sizeTransform_x, (176 - 162) * transformY * sizeTransform_y));
		Platform5->setPhysicsBody(bodyPlatform5);
		this->addChild(Platform5);
	}
	
	{
		// �����߽�����Ӵ�
		auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT);
		auto edgeNode = Node::create();
		edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		edgeNode->setPhysicsBody(body);
		this->addChild(edgeNode);
	}

	//��ʼ����ҿ��ƽ�ɫ
	//hero1.hero->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	hero1.sprite->setPosition(origin.x+visibleSize.width/2, origin.y+visibleSize.height-hero1.sprite->getContentSize().height);
	auto bodyplayer = PhysicsBody::createBox(hero1.sprite->getContentSize());
	hero1.sprite->setPhysicsBody(bodyplayer);
	this->addChild(hero1.sprite);

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
	EventListenerMouse* _mouseListener = EventListenerMouse::create();
	//_mouseListener->onMouseMove = CC_CALLBACK_1(StartScene::onMouseMove, this);
	//_mouseListener->onMouseUp = CC_CALLBACK_1(StartScene::onMouseUp, this);
	_mouseListener->onMouseDown = CC_CALLBACK_1(GameScene::onMouseDown, this);
	//_mouseListener->onMouseScroll = CC_CALLBACK_1(StartScene::onMouseScroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

	//���º���
	this->scheduleUpdate();

	return true;
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)
{
	KeyMap[keycode] = true;
	
	auto Jump = JumpBy::create(1, Vec2(0,80), 80, 1);
	if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_SPACE|| keycode == cocos2d::EventKeyboard::KeyCode::KEY_W)
		hero1.sprite->runAction(MoveBy::create(0.5,Vec2(0,hero1.sprite->getContentSize().height*3)));
	if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_S)
		hero1.sprite->runAction(MoveBy::create(0.5,Vec2(0, -hero1.sprite->getContentSize().height*2)));
}


void GameScene::onMouseDown(Event* event)
{
	/*��ʱ��갴�£����Խ����йصĲ���*/
	return;
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
}