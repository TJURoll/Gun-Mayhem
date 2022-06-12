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

	//continue��ť��ǰ��GameScene
	auto ContinueButton = ui::Button::create("Continue1.jpg", "Continue2.jpg");
	ContinueButton->setScale(0.8f);
	ContinueButton->addTouchEventListener(CC_CALLBACK_2(RoomScene::ContinuebuttonCallBack, this));
	ContinueButton->setPosition(Vec2(origin.x + visibleSize.width * 6 / 7, origin.y + visibleSize.height * 2 / 7));
	this->addChild(ContinueButton);

	

	//AI����ѡ��
	auto none = Sprite::create("none.jpg");//������������
	auto AI2 = Sprite::create("AI2.jpg");
	none->setScale(0.3f);
	AI2->setScale(0.3f);
	auto noneSpriteItem = MenuItemSprite::create(none, none);//������������˵���
	auto AI2SpriteItem = MenuItemSprite::create(AI2, AI2);
	auto toggleItem = MenuItemToggle::createWithCallback([&](Ref* ref) {
		//��������ai������none����1��AI2����2
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

		}, noneSpriteItem, AI2SpriteItem, NULL);//����һ�����ز˵���

	toggleItem->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	toggleItem->setPosition(Vec2(origin.x + visibleSize.width * 4 / 5, origin.y + visibleSize.height * 5 / 12));
	
	//�Ƿ�Ϊ����������ȫ�ֱ���
	bool Life_infinite;
	//����������ť
	auto Life1 = Sprite::create("life1.jpg");//������������
	auto Life2 = Sprite::create("life2.jpg");
	Life1->setScale(1.5f);
	Life2->setScale(1.5f);
	auto Life1SpriteItem = MenuItemSprite::create(Life1, Life1);//������������˵���
	auto Life2SpriteItem = MenuItemSprite::create(Life2, Life2);
	auto toggleItem2 = MenuItemToggle::createWithCallback([&](Ref* ref) {
		auto item2 = dynamic_cast<MenuItemToggle*>(ref);
		if (item2) {
			if (item2->getSelectedIndex() == 0) {
				CCLOG("limited life");
				Life_infinite = false;
			}
			else if (item2->getSelectedIndex() == 1) {
				CCLOG("infinite life");
				Life_infinite =true;
			}
		}

		}, Life1SpriteItem, Life2SpriteItem, NULL);//����һ�����ز˵���

	toggleItem2->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	toggleItem2->setPosition(Vec2(origin.x + visibleSize.width * 3 / 5, origin.y + visibleSize.height * 3 / 14));

	//����һ���˵�
	Menu* menu = Menu::create(toggleItem,toggleItem2,NULL);
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
		Director::getInstance()->replaceScene(StartScene::create());
		break;
	default:
		break;
	}
}


void RoomScene::ContinuebuttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		g_NumOfAI = AInum;
		Director::getInstance()->replaceScene(GameScene::createScene());
		break;
	default:
		break;
	}
}
