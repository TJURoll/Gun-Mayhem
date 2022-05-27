#include "HelloWorldScene.h"
#include "StartScene.h" 
USING_NS_CC;


// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	if (!Scene::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sprite = Sprite::create("logo.jpeg");
	if (sprite == nullptr)
	{
		problemLoading("'logo.jpeg'");
	}
	else
	{
		sprite->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
		sprite->setTextureRect(Rect(0, 0, 0.85f * sprite->getContentSize().width, sprite->getContentSize().height));
		this->addChild(sprite, 0);
	}
	this->scheduleOnce(CC_SCHEDULE_SELECTOR(HelloWorld::SwitchToStartScene), 3.0f);
	return true;
}


void HelloWorld::SwitchToStartScene(float ft)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.f, StartScene::create()));
}
