#include "RoomScene.h" 
#include"StartScene.h"
#include"GameScene.h"
Scene* RoomScene::createScene()
{
	return RoomScene::create();
}
bool RoomScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("Room.jpg");
	background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	background->setPosition(origin.x, origin.y);
	auto contentSize = background->getContentSize();
	background->setScale(visibleSize.width / contentSize.width, visibleSize.height / contentSize.height);;
	this->addChild(background);

	auto BackToMenuButton = ui::Button::create("Backtomenu.png", "Backtomenu2.png");
	BackToMenuButton->setScale(0.5f);
	BackToMenuButton->addTouchEventListener(CC_CALLBACK_2(RoomScene::buttonCallBack, this));
	BackToMenuButton->setPosition(Vec2(origin.x + visibleSize.width * 6 / 7, origin.y + visibleSize.height * 1 / 7));
	this->addChild(BackToMenuButton);

	//continue按钮，前往GameScene
	auto ContinueButton = ui::Button::create("Continue1.jpg", "Continue2.jpg");
	ContinueButton->setScale(0.8f);
	ContinueButton->addTouchEventListener(CC_CALLBACK_2(RoomScene::ContinuebuttonCallBack, this));
	ContinueButton->setPosition(Vec2(origin.x + visibleSize.width * 6 / 7, origin.y + visibleSize.height * 2 / 7));
	this->addChild(ContinueButton);


	//AI数量选择
	auto none = Sprite::create("none.jpg");//创建两个精灵
	auto AI2 = Sprite::create("AI2.jpg");
	none->setScale(0.3f);
	AI2->setScale(0.3f);
	auto noneSpriteItem = MenuItemSprite::create(none, none);//创建两个精灵菜单项
	auto AI2SpriteItem = MenuItemSprite::create(AI2, AI2);
	auto toggleItem = MenuItemToggle::createWithCallback([&](Ref* ref) {
	//函数返回ai个数。none返回1，AI2返回2
		auto item = dynamic_cast<MenuItemToggle*>(ref);
		if (item) {
			if (item->getSelectedIndex() == 0) {
				CCLOG("AI=1");
				setAInum(1);
			}
			else if (item->getSelectedIndex() == 1) {
				CCLOG("AI=2");
				setAInum(2);
			}
		}
		
		}, noneSpriteItem, AI2SpriteItem, NULL);//创建一个开关菜单项
	
	toggleItem->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	toggleItem->setPosition(Vec2(origin.x + visibleSize.width * 4/5, origin.y + visibleSize.height * 5/12));

	//创建一个菜单
	Menu* menu = Menu::create(toggleItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
	return true;
}

void RoomScene::setAInum(int num) {
	AInum = num;
}


void RoomScene::buttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
		case Widget::TouchEventType::ENDED:
			Director::getInstance()->popScene();
			break;
		default:
			break;
	}
}

void RoomScene::ContinuebuttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
		case Widget::TouchEventType::ENDED:
			//Director::getInstance()->replaceScene(GameScene::create());
			Director::getInstance()->pushScene(GameScene::createScene());
			break;
		default:
			break;
	}
}
