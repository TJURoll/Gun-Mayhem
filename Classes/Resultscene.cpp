#include "StartScene.h" 
#include "GameScene.h"
#include "ResultScene.h"
//调用ResultScene的时候,呈现渐变显示。
// 用 Director::getInstance()->pushScene(TransitionFade::create(2.0f, ResultScene::create()));;来调用

Scene* ResultScene::createScene()
{
	return ResultScene::create();
}


bool ResultScene::init()
{
	if (!Scene::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//插入胜利的背景图片
	auto win = Sprite::create("Win.jpg");
	win->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	win->setPosition(Vec2(origin.x, origin.y));
	auto contentSize = win->getContentSize();
	win->setScale(visibleSize.width / contentSize.width, visibleSize.height / contentSize.height);
	if(g_Win)
		this->addChild(win);

	//插入失败的背景图片
	auto fail = Sprite::create("Fail.jpg");
	fail->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	fail->setPosition(Vec2(origin.x, origin.y));
	auto contentSize2 = fail->getContentSize();
	fail->setScale(visibleSize.width / contentSize2.width, visibleSize.height / contentSize2.height);
	if(!g_Win)
		this->addChild(fail);

	this->scheduleOnce(CC_SCHEDULE_SELECTOR(ResultScene::SwitchToStartScene), 3.0f);//延迟切换场景
	return true;
}
void ResultScene::SwitchToStartScene(float ft)
{
	Director::getInstance()->replaceScene(TransitionFade::create(2.f, StartScene::create()));
}

