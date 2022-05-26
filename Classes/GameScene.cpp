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

	/*获取原始视窗大小*/
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/*创建背景变量*/
	auto background = Sprite::create("Map.png");
	background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	background->setPosition(origin.x, origin.y);
	auto contentSize = background->getContentSize();
	background->setScale(visibleSize.width / contentSize.width, visibleSize.height / contentSize.height);
	this->addChild(background);

	/*创建障碍物精灵*/
	auto blockSprite1= Sprite::create("six_blocks.png");//左下6型障碍物，这里指的X型障碍物指的是由X块砖块构成的障碍物
	Vec2 positionOfBlock1;
	positionOfBlock1.setPoint(78,95);
	putBarrier(blockSprite1, positionOfBlock1,0.90f);

	auto blockSprite2 = Sprite::create("six_blocks.png");//右下6型障碍物
	Vec2 positionOfBlock2;
	positionOfBlock2.setPoint(257, 95);
	putBarrier(blockSprite2, positionOfBlock2, 0.90f);

	auto blockSprite3 = Sprite::create("three_blocks.png");//最上3型障碍物
	Vec2 positionOfBlock3;
	positionOfBlock3.setPoint(200, 221);
	putBarrier(blockSprite3, positionOfBlock3, 0.90f);

	auto blockSprite4 = Sprite::create("three_blocks.png");//右侧3型障碍物
	Vec2 positionOfBlock4;
	positionOfBlock4.setPoint(280, 165);
	putBarrier(blockSprite4, positionOfBlock4, 0.90f);

	auto blockSprite5 = Sprite::create("three_blocks.png");//左侧3型障碍物
	Vec2 positionOfBlock5;
	positionOfBlock5.setPoint(128, 165);
	putBarrier(blockSprite5, positionOfBlock5, 0.90f);

	/*以下创建监视器部分取自官方文档以及CSDN*/
	/*创建键盘监视器*/
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	/*创建鼠标监视器*/
	EventListenerMouse* _mouseListener = EventListenerMouse::create();
	//_mouseListener->onMouseMove = CC_CALLBACK_1(StartScene::onMouseMove, this);
	//_mouseListener->onMouseUp = CC_CALLBACK_1(StartScene::onMouseUp, this);
	_mouseListener->onMouseDown = CC_CALLBACK_1(GameScene::onMouseDown, this);
	//_mouseListener->onMouseScroll = CC_CALLBACK_1(StartScene::onMouseScroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

	/*设置玩家初始位置*/
	hero1.hero ->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	hero1.hero->setPosition(origin.x, origin.y);
	this->addChild(hero1.hero);

	/*定义刷新器*/
	scheduleUpdate();

	return true;
}

void GameScene::putBarrier(Sprite* barrier, const Vec2 position,float scaleRate)//此时postion为需要放置的位置，visible直接用之前获取视窗大小即可
{
	barrier->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	barrier->setPosition(position.x, position.y);
	barrier->setScale(scaleRate);
	this->addChild(barrier);
}

/*
*此段使得英雄能够连续移动的部分参考了CSDN中cocos2dx-9.键盘事件-实现精灵的连续移动文章的思路
*链接：https://blog.csdn.net/weixin_44453949/article/details/110885967
*/

void GameScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)
{
	int x=0, y=0;//移动的长度
	bool whetherJump = false;//判断是否跳跃
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
	int yStep = 0;//定义沿着y轴方向走的距离
	int xStep = 0;//定义沿着x轴方向走的距离

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
	/*获取跳跃之后目标坐标，并且进行判断*/
	Vec2 srcPosition = Hero->hero->getPosition();
	srcPosition.y += jumpHeight;
	srcPosition.x += jumpHeight;
	if (!Hero->whetherCanMove(srcPosition))
		return;//如果没法跳跃（遇到边界或者障碍物，直接不动或者坐假动作)
#if 0
	auto moveTo = MoveTo::create(0.1f, srcPosition);
	Hero->hero->runAction(moveTo);
#else
	/*此时英雄会向右上跳跃7个单位长度,下面是逐帧动画的制作（共计14帧）*/
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("monster/monster.plist");
	//Sprite* tempflash = Sprite::createWithSpriteFrameName("1");
	//Hero->hero->setPosition(Hero->hero->getPosition());//使得新创立的精灵和原先的精灵重合
	//Hero->hero->setVisible(false);//将原先的精灵进行屏蔽
	//this->addChild(tempflash);//将新创立的精灵加入场景中

	/*创建需要的精灵帧*/
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
	//Hero->hero->setVisible(true);//将原先的精灵进行恢复
#endif
}

void GameScene::onMouseDown(Event* event)
{
	/*此时鼠标按下，可以进行有关的操作*/
	return;
}




