#include "HelloWorldScene.h"
#include "StartScene.h" 
USING_NS_CC;


bool HelloWorld::init()
{
	if (!Scene::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Ìí¼ÓlogoÍ¼Æ¬
	auto sprite = Sprite::create("logo.jpeg");
	if (sprite == nullptr)
	{
		return false;
	}
	else
	{
		sprite->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
		sprite->setTextureRect(Rect(0, 0, 0.85f * sprite->getContentSize().width, sprite->getContentSize().height));
		this->addChild(sprite, 0);
	}
	this->scheduleOnce(CC_SCHEDULE_SELECTOR(HelloWorld::SwitchToStartScene), 3.0f);//ÑÓ³ÙÇÐ»»³¡¾°
	return true;
}


void HelloWorld::SwitchToStartScene(float ft)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Start.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Game.mp3");
	Director::getInstance()->replaceScene(TransitionFade::create(1.f, StartScene::create()));
}
