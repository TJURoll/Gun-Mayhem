#include "StartScene.h" 
#include "GameScene.h"
//创建GameScene后取消注释上句完成场景切换
Scene* StartScene::createScene()
{
	return StartScene::create();
}
bool StartScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("background.png");
	background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	background->setPosition(origin.x, origin.y);
	auto contentSize = background->getContentSize();
	background->setScale(visibleSize.width / contentSize.width, visibleSize.height / contentSize.height);;
	this->addChild(background);

	auto label = Label::createWithTTF("Gun Mayhem", "fonts/Marker Felt.ttf", 24);
	label->setTextColor(Color4B::BLUE);
	label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	label->setPosition(visibleSize.width / 8, visibleSize.height * 9 / 10);
	this->addChild(label);

	auto StartGameButton = ui::Button::create("choice.png", "unchoice.png");
	StartGameButton->setScale(0.5);
	StartGameButton->setTitleText("START");
	StartGameButton->setTitleColor(Color3B::WHITE);
	StartGameButton->setTitleFontSize(20);
	StartGameButton->addTouchEventListener(CC_CALLBACK_2(StartScene::buttonCallBack, this));
	StartGameButton->setPosition(Vec2(origin.x + visibleSize.width * 4 / 5, origin.y + visibleSize.height * 3 / 5));
	this->addChild(StartGameButton);
	return true;
}

void StartScene::buttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->replaceScene(GameScene::createScene());
		//创建GameScene后取消注释上句完成场景切换
		break;
	default:
		break;
	}
}
