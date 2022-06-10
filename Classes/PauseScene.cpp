#include "StartScene.h" 
#include "GameScene.h"
#include "PauseScene.h"
#include "RoomScene.h"
#include "Control_SettingScene.h"
#include "AudioEngine.h"
//USING_NS_CC;
//using namespace experimental;

/*��gamescene�а�P������������档��Gamescene���̿��Ʋ����м����������
if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_P)
		Director::getInstance()->pushScene(PauseScene::createScene());
�ǵ���GameScene��cpp�м�PauseScene��ͷ�ļ�
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

	//���ñ���ͼƬ
	auto background = Sprite::create("Pause.jpg");
	background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	background->setPosition(Vec2(origin.x, origin.y));
	auto contentSize = background->getContentSize();
	background->setScale(visibleSize.width / contentSize.width, visibleSize.height / contentSize.height);
	this->addChild(background);

	//continue��ť��ǰ��GameScene
	auto ContinueButton = ui::Button::create("continue.png", "continue2.png");
	ContinueButton->setScale(1.3f);
	ContinueButton->addTouchEventListener(CC_CALLBACK_2(PauseScene::continuebuttonCallBack, this));
	ContinueButton->setPosition(Vec2(origin.x + visibleSize.width * 1 / 4, origin.y + visibleSize.height * 1 / 2));
	this->addChild(ContinueButton);

	//again��ť��ǰ��RoomScene
	auto AgainButton = ui::Button::create("again.png", "again2.png");
	AgainButton->setScale(1.3f);
	AgainButton->addTouchEventListener(CC_CALLBACK_2(PauseScene::againbuttonCallBack, this));
	AgainButton->setPosition(Vec2(origin.x + visibleSize.width * 1 / 2, origin.y + visibleSize.height * 23 / 48));
	this->addChild(AgainButton);

	//menu��ť��ǰ��StartScene
	auto MenuButton = ui::Button::create("menu.png", "menu2.png");
	MenuButton->setScale(1.3f);
	MenuButton->addTouchEventListener(CC_CALLBACK_2(PauseScene::menubuttonCallBack, this));
	MenuButton->setPosition(Vec2(origin.x + visibleSize.width * 3 / 4, origin.y + visibleSize.height * 1 / 2));
	this->addChild(MenuButton);

	//���������Ļ�����
	auto slider = Slider::create();
	this->addChild(slider);
	//���û���������
	slider->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	slider->setPosition(Vec2(origin.x + visibleSize.width * 1 / 4, origin.y - visibleSize.height * 1 / 12));
	//���ػ���������Դ
	slider->loadBarTexture("s1.png");
	slider->loadProgressBarTexture("s2.png");
	slider->loadSlidBallTextures("button1.png", "button2.png", "button3.png");
	slider->setPercent(static_cast<int>(SimpleAudioEngine::getInstance()->getBackgroundMusicVolume() * 100));//���û������ڰٷֱ�
	slider->addEventListener([&](Ref* ref, Slider::EventType type)
		{
			if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
				//�ٷֱȱ仯ʱ����Ӧ�ı����������Ĵ�С
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
		Director::getInstance()->popScene();//����ͣ����pop�����ص�gamescene����
		break;
	default:
		break;
	}
}
void PauseScene::againbuttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->replaceScene(RoomScene::create());//�ص�roomscene����
		break;
	default:
		break;
	}
}
void PauseScene::menubuttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->replaceScene(StartScene::create());//�ص�startscene����
		break;
	default:
		break;
	}
}