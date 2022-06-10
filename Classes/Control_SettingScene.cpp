#include "Control_SettingScene.h" 
#include"StartScene.h"

Scene* ControlSettingScene::createScene()
{
	return ControlSettingScene::create();
}
bool ControlSettingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//创建背景
	auto background = Sprite::create("settingsbackground.jpg");
	background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	background->setPosition(origin.x, origin.y);
	auto contentSize = background->getContentSize();
	background->setScale(visibleSize.width / contentSize.width, visibleSize.height / contentSize.height);;
	this->addChild(background);

	auto BackToMenuButton = ui::Button::create("Backtomenu.png", "Backtomenu2.png");
	BackToMenuButton->setScale(0.5f);
	BackToMenuButton->addTouchEventListener(CC_CALLBACK_2(ControlSettingScene::buttonCallBack, this));
	BackToMenuButton->setPosition(Vec2(origin.x + visibleSize.width * 6 / 7, origin.y + visibleSize.height * 1 / 7));
	this->addChild(BackToMenuButton);

	//开启音乐按钮
	auto on = Sprite::create("on.jpg");//创建两个精灵
	auto off = Sprite::create("off.jpg");
	on->setScale(0.5f);
	off->setScale(0.5f);
	auto onSpriteItem = MenuItemSprite::create(on, on);//创建两个精灵菜单项
	auto offSpriteItem = MenuItemSprite::create(off, off);

	//根据音乐播放情况创建开关菜单项
	MenuItemToggle* toggleItem;
	if (SimpleAudioEngine::getInstance()->getBackgroundMusicVolume()) {
		CCLOG("On init");
		toggleItem = MenuItemToggle::createWithCallback(
			[&](Ref* ref) {
				auto item = dynamic_cast<MenuItemToggle*>(ref);
				if (item) {
					if (item->getSelectedIndex() == 0) {
						CCLOG("Play sound");
						SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.f);
					}
					else if (item->getSelectedIndex() == 1) {
						CCLOG("Silence");
						SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.f);
					}
				}
			}, onSpriteItem, offSpriteItem, NULL);
	}
	else {
		toggleItem = MenuItemToggle::createWithCallback(
			[&](Ref* ref) {
				auto item = dynamic_cast<MenuItemToggle*>(ref);
				if (item) {
					if (item->getSelectedIndex() == 0) {
						CCLOG("Play sound");
						SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.f);
					}
					else if (item->getSelectedIndex() == 1) {
						CCLOG("Silence");
						SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.f);
					}
				}
			}, offSpriteItem, onSpriteItem, NULL);
	}
	toggleItem->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	toggleItem->setPosition(Vec2(origin.x + visibleSize.width * 29 / 32, origin.y + visibleSize.height * 17 / 28));

	//开启音效按钮
	auto on2 = Sprite::create("on.jpg");//创建两个精灵
	auto off2 = Sprite::create("off.jpg");
	on2->setScale(0.5f);
	off2->setScale(0.5f);
	auto onSpriteItem2 = MenuItemSprite::create(on2, on2);//创建两个精灵菜单项
	auto offSpriteItem2 = MenuItemSprite::create(off2, off2);
	MenuItemToggle* toggleItem2;
	if (SimpleAudioEngine::getInstance()->getEffectsVolume()) {
		CCLOG("On init");
		toggleItem2 = MenuItemToggle::createWithCallback(
			[&](Ref* ref) {
				auto item = dynamic_cast<MenuItemToggle*>(ref);
				if (item) {
					if (item->getSelectedIndex() == 0) {
						CCLOG("Play sound");
						SimpleAudioEngine::getInstance()->setEffectsVolume(1.f);
					}
					else if (item->getSelectedIndex() == 1) {
						CCLOG("Silence");
						SimpleAudioEngine::getInstance()->setEffectsVolume(0.f);
					}
				}
			}, onSpriteItem2, offSpriteItem2, NULL);
	}
	else {
		toggleItem2 = MenuItemToggle::createWithCallback(
			[&](Ref* ref) {
				auto item = dynamic_cast<MenuItemToggle*>(ref);
				if (item) {
					if (item->getSelectedIndex() == 0) {
						CCLOG("Play sound");
						SimpleAudioEngine::getInstance()->setEffectsVolume(0.f);
					}
					else if (item->getSelectedIndex() == 1) {
						CCLOG("Silence");
						SimpleAudioEngine::getInstance()->setEffectsVolume(1.f);
					}
				}
			}, offSpriteItem2, onSpriteItem2, NULL);
	}
	toggleItem2->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	toggleItem2->setPosition(Vec2(origin.x + visibleSize.width * 29 / 32, origin.y + visibleSize.height * 11 / 28));
	//创建一个菜单
	Menu* menu = Menu::create(toggleItem, toggleItem2, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
	return true;
}


void ControlSettingScene::buttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->popScene();
		break;
	default:
		break;
	}


}
