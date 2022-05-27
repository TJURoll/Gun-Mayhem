#include "GameScene.h"
#include "HelloWorldScene.h"
#include "StartScene.h" 
USING_NS_CC;

cocos2d::Scene* GameScene::createScene()
{
	return GameScene::create();
}

bool GameScene::init()
{
	if (!Scene::init())
		return false;

	/*��ȡԭʼ�Ӵ���С*/
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/*������������*/
	auto background = Sprite::create("Map.png");
	background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	background->setPosition(origin.x, origin.y);
	auto contentSize = background->getContentSize();
	background->setScale(visibleSize.width / contentSize.width, visibleSize.height / contentSize.height);
	this->addChild(background);

	/*�����ϰ��ﾫ��*/
	auto blockSprite1= Sprite::create("six_blocks.png");//����6���ϰ������ָ��X���ϰ���ָ������X��ש�鹹�ɵ��ϰ���
	Vec2 positionOfBlock1;
	positionOfBlock1.setPoint(78,95);
	putBarrier(blockSprite1, positionOfBlock1,0.90f);

	auto blockSprite2 = Sprite::create("six_blocks.png");//����6���ϰ���
	Vec2 positionOfBlock2;
	positionOfBlock2.setPoint(257, 95);
	putBarrier(blockSprite2, positionOfBlock2, 0.90f);

	auto blockSprite3 = Sprite::create("three_blocks.png");//����3���ϰ���
	Vec2 positionOfBlock3;
	positionOfBlock3.setPoint(200, 221);
	putBarrier(blockSprite3, positionOfBlock3, 0.90f);

	auto blockSprite4 = Sprite::create("three_blocks.png");//�Ҳ�3���ϰ���
	Vec2 positionOfBlock4;
	positionOfBlock4.setPoint(280, 165);
	putBarrier(blockSprite4, positionOfBlock4, 0.90f);

	auto blockSprite5 = Sprite::create("three_blocks.png");//���3���ϰ���
	Vec2 positionOfBlock5;
	positionOfBlock5.setPoint(128, 165);
	putBarrier(blockSprite5, positionOfBlock5, 0.90f);

	/*���´�������������ȡ�Թٷ��ĵ��Լ�CSDN*/
	/*�������̼�����*/
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	/*������������*/
	EventListenerMouse* _mouseListener = EventListenerMouse::create();
	//_mouseListener->onMouseMove = CC_CALLBACK_1(StartScene::onMouseMove, this);
	//_mouseListener->onMouseUp = CC_CALLBACK_1(StartScene::onMouseUp, this);
	_mouseListener->onMouseDown = CC_CALLBACK_1(GameScene::onMouseDown, this);
	//_mouseListener->onMouseScroll = CC_CALLBACK_1(StartScene::onMouseScroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

	/*������ҳ�ʼλ��*/
	hero1.hero ->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	hero1.hero->setPosition(origin.x, origin.y);
	this->addChild(hero1.hero);

	/*����ˢ����*/
	scheduleUpdate();

	return true;
}

void GameScene::putBarrier(Sprite* barrier, const Vec2 position,float scaleRate)//��ʱpostionΪ��Ҫ���õ�λ�ã�visibleֱ����֮ǰ��ȡ�Ӵ���С����
{
	barrier->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	barrier->setPosition(position.x, position.y);
	barrier->setScale(scaleRate);
	this->addChild(barrier);
}

/*
*�˶�ʹ��Ӣ���ܹ������ƶ��Ĳ��ֲο���CSDN��cocos2dx-9.�����¼�-ʵ�־���������ƶ����µ�˼·
*���ӣ�https://blog.csdn.net/weixin_44453949/article/details/110885967
*/

void GameScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)
{
	int x=0, y=0;//�ƶ��ĳ���
	bool whetherJump = false;//�ж��Ƿ���Ծ
	keyMap.clear();
	switch (keycode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		keyMap[cocos2d::EventKeyboard::KeyCode::KEY_W] = true;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		keyMap[cocos2d::EventKeyboard::KeyCode::KEY_S] = true;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		keyMap[cocos2d::EventKeyboard::KeyCode::KEY_A] = true;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		keyMap[cocos2d::EventKeyboard::KeyCode::KEY_D] = true;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
		whetherJump=true;
		break;
	default:
		break;
	}

	if (whetherJump == true)
		jumpTo(&hero1,7);
	//this->update();
}
void  GameScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	switch (keycode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		keyMap[cocos2d::EventKeyboard::KeyCode::KEY_W] = false;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		keyMap[cocos2d::EventKeyboard::KeyCode::KEY_S] = false;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		keyMap[cocos2d::EventKeyboard::KeyCode::KEY_A] = false;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		keyMap[cocos2d::EventKeyboard::KeyCode::KEY_D] = false;
		break;
	}
	//this->update();
}

void GameScene::update(float delta)
{
	int yStep = 0;//��������y�᷽���ߵľ���
	int xStep = 0;//��������x�᷽���ߵľ���

	if (keyMap[cocos2d::EventKeyboard::KeyCode::KEY_W])
		yStep = 1;
	if (keyMap[cocos2d::EventKeyboard::KeyCode::KEY_S])
		yStep = -1;
	if (keyMap[cocos2d::EventKeyboard::KeyCode::KEY_A])
		xStep = -1;
	if (keyMap[cocos2d::EventKeyboard::KeyCode::KEY_D])
		xStep = 1;

	auto moveto = MoveTo::create(0.2f, Vec2(this->hero1.hero->getPosition().x + xStep, this->hero1.hero->getPosition().y+ yStep));
	this->hero1.hero->runAction(moveto);

}

void GameScene::jumpTo(Hero1* Hero, int jumpHeight)
{
	/*��ȡ��Ծ֮��Ŀ�����꣬���ҽ����ж�*/
	Vec2 srcPosition = Hero->hero->getPosition();
	srcPosition.y += jumpHeight;
	srcPosition.x += jumpHeight;
	if (!Hero->whetherCanMove(srcPosition))
		return;//���û����Ծ�������߽�����ϰ��ֱ�Ӳ����������ٶ���)
#if 0
	auto moveTo = MoveTo::create(0.1f, srcPosition);
	Hero->hero->runAction(moveTo);
#else
	/*��ʱӢ�ۻ���������Ծ7����λ����,��������֡����������������14֡��*/
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("monster/monster.plist");
	//Sprite* tempflash = Sprite::createWithSpriteFrameName("1");
	//Hero->hero->setPosition(Hero->hero->getPosition());//ʹ���´����ľ����ԭ�ȵľ����غ�
	//Hero->hero->setVisible(false);//��ԭ�ȵľ����������
	//this->addChild(tempflash);//���´����ľ�����볡����

	/*������Ҫ�ľ���֡*/
	Vector<SpriteFrame*>flash;
	for (int i = 1; i < 13; i++) {
		flash.pushBack(cache->getSpriteFrameByName(Value(i).asString()));
	}

	Animation* animation = Animation::createWithSpriteFrames(flash, 0.5f / flash.size());
	Animate* animate = Animate::create(animation);

	/*auto animation = Animation::create();
	char nametag[20] = { '\0'};
	for (int i = 1; i < 13; i++) {
		sprintf(nametag, ".\\monsterAni%d.png", i);
		animation->addSpriteFrameWithFile(nametag);
	}
	animation->setDelayPerUnit(0.02f);
	animation->setLoops(1);
	auto animate = Animate::create(animation);*/


	auto moveTo = MoveTo::create(0.1f, srcPosition);
	Hero->hero->runAction(Spawn::create(animate, moveTo));

	//this->removeChild(tempflash);
	//Hero->hero->setVisible(true);//��ԭ�ȵľ�����лָ�
#endif
}

void GameScene::onMouseDown(Event* event)
{
	/*��ʱ��갴�£����Խ����йصĲ���*/
	return;
}




