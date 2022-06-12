#include "StartScene.h" 
#include "Control_SettingScene.h" 
#include "GameScene.h"
#include "RoomScene.h"

bool StartScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	//背景音乐控制
	auto instance = CocosDenshion::SimpleAudioEngine::getInstance();
	float volume;
	if (!instance->isBackgroundMusicPlaying())
		volume = 1.0f;
	else {
		volume = instance->getBackgroundMusicVolume();
		instance->stopBackgroundMusic(); //stop后无法恢复播放
	}
	instance->playBackgroundMusic("Music/Start.mp3", true);
	instance->setBackgroundMusicVolume(volume);

	//设置背景图片
	auto background = Sprite::create("background.png");
	background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	background->setPosition(Vec2(origin.x, origin.y));
	auto contentSize = background->getContentSize();
	background->setScale(visibleSize.width / contentSize.width, visibleSize.height / contentSize.height);
	this->addChild(background);

	//添加游戏标题
	auto label = Label::createWithTTF("Gun Mayhem", "fonts/Marker Felt.ttf", 96);
	label->setTextColor(Color4B::GRAY);
	label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	label->setPosition(origin.x + visibleSize.width / 20, origin.y + visibleSize.height * 19 / 20);
	label->setScaleX(1.3f);
	label->enableShadow();
	this->addChild(label);

	//添加一把枪
	auto gun = Sprite::create("guns.png");
	gun->setRotation(-45);
	gun->setTextureRect(Rect(0, 0, 100.f, 30.f));
	gun->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	gun->setPosition(label->getPosition().x + label->getContentSize().width * 1.3f + gun->getContentSize().width / 2, label->getPosition().y - gun->getContentSize().height / 2 - 15);
	gun->setScale(1.5f);
	this->addChild(gun);

	//按钮创建
	auto startGameButton = buttonCreate("Start", [](Ref* ref, Widget::TouchEventType type)
		{
			switch (type) {
			case Widget::TouchEventType::ENDED:
				Director::getInstance()->replaceScene(RoomScene::createScene());
				break;
			default:
				break;
			}
		});
	auto settingsButton = buttonCreate("Settings", [](Ref* ref, Widget::TouchEventType type)
		{
			switch (type) {
			case Widget::TouchEventType::ENDED:
				Director::getInstance()->pushScene(ControlSettingScene::createScene());
				break;
			default:
				break;
			}
		});
	auto exitButton = buttonCreate("Exit", [](Ref* ref, Widget::TouchEventType type)
		{
			switch (type) {
			case Widget::TouchEventType::ENDED:
				Director::getInstance()->end();
				break;
			default:
				break;
			}
		});
	buttonAdd({ startGameButton,settingsButton,exitButton });//将按钮添加到屏幕上
	return true;
}

Button* StartScene::buttonCreate(const std::string& titleText, pFunc switchSceneEvent)const
{
	Button* p = new(std::nothrow) Button;
	if (p == nullptr)
	{
		return nullptr;
	}
	p = Button::create("choice.png", "unchoice.png");
	p->setTitleText(titleText);
	p->setTitleColor(Color3B::WHITE);
	p->setTitleFontName("fonts/Marker Felt.ttf");
	p->setTitleFontSize(48);
	p->addTouchEventListener(switchSceneEvent);
	return p;
}

void StartScene::buttonAdd(const std::vector<Button*> &buttonList)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	for (auto iterator = buttonList.begin(); iterator < buttonList.end(); iterator++)
	{
		(*iterator)->setPosition(Vec2(origin.x + visibleSize.width * 4 / 5,
			origin.y + visibleSize.height * 3 / 5 - (iterator - buttonList.begin()) * 1.7f * (*iterator)->getContentSize().height));
		this->addChild(*iterator);
	}

}