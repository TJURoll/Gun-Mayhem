#include "StartScene.h" 
#include "GameScene.h"
#include "PauseScene.h"
#include "RoomScene.h"
#include "Control_SettingScene.h"
#include "AudioEngine.h"
//USING_NS_CC;
//using namespace experimental;

/*在gamescene中按P，进入这个界面。在Gamescene键盘控制部分中加入以下这句
if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_P)
		Director::getInstance()->pushScene(PauseScene::createScene());
记得在GameScene的cpp中加PauseScene的头文件
*/


Scene* PauseScene::createScene()
{
	return PauseScene::create();
}
bool PauseScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//设置背景图片
	auto background = Sprite::create("Pause.jpg");
	background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	background->setPosition(Vec2(origin.x, origin.y));
	auto contentSize = background->getContentSize();
	background->setScale(visibleSize.width / contentSize.width, visibleSize.height / contentSize.height);
	this->addChild(background);

	//continue按钮，前往GameScene
	auto ContinueButton = ui::Button::create("continue.png", "continue2.png");
	ContinueButton->setScale(1.3f);
	ContinueButton->addTouchEventListener(CC_CALLBACK_2(PauseScene::continuebuttonCallBack, this));
	ContinueButton->setPosition(Vec2(origin.x + visibleSize.width * 1 / 4, origin.y + visibleSize.height * 1 / 2));
	this->addChild(ContinueButton);

	//again按钮，前往RoomScene
	auto AgainButton = ui::Button::create("again.png", "again2.png");
	AgainButton->setScale(1.3f);
	AgainButton->addTouchEventListener(CC_CALLBACK_2(PauseScene::againbuttonCallBack, this));
	AgainButton->setPosition(Vec2(origin.x + visibleSize.width * 1 / 2, origin.y + visibleSize.height * 23 / 48));
	this->addChild(AgainButton);

	//menu按钮，前往StartScene
	auto MenuButton = ui::Button::create("menu.png", "menu2.png");
	MenuButton->setScale(1.3f);
	MenuButton->addTouchEventListener(CC_CALLBACK_2(PauseScene::menubuttonCallBack, this));
	MenuButton->setPosition(Vec2(origin.x + visibleSize.width * 3 / 4, origin.y + visibleSize.height * 1 / 2));
	this->addChild(MenuButton);

	//创建声音的滑动条
	auto slider = Slider::create();
	this->addChild(slider);
	//设置滑动条坐标
	slider->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	slider->setPosition(Vec2(origin.x + visibleSize.width * 1 / 4, origin.y - visibleSize.height * 1 / 12));
	//加载滑条滑块资源
	slider->loadBarTexture("s1.png");
	slider->loadProgressBarTexture("s2.png");
	slider->loadSlidBallTextures("button1.png", "button2.png", "button3.png");
	slider->setPercent(static_cast<int>(SimpleAudioEngine::getInstance()->getBackgroundMusicVolume() * 100));//设置滑块所在百分比
	slider->addEventListener([&](Ref* ref, Slider::EventType type)
		{
			if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
				//百分比变化时，对应改变声音音量的大小
				int percent = dynamic_cast<Slider*>(ref)->getPercent();
				log("slider is moving");
				log("%d", percent);
				SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(percent / 100.f);
			}
		}
	);
	return true;
}
void PauseScene::continuebuttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->popScene();//把暂停界面pop掉，回到gamescene界面
		break;
	default:
		break;
	}
}
void PauseScene::againbuttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->replaceScene(RoomScene::create());//回到roomscene界面
		break;
	default:
		break;
	}
}
void PauseScene::menubuttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->replaceScene(StartScene::create());//回到startscene界面
		break;
	default:
		break;
	}
}