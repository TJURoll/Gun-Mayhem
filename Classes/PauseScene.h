#ifndef _PAUSESCENE_
#define _PAUSESCENE_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/SimpleAudioEngine.h"

using namespace cocos2d;
using namespace ui;
using namespace CocosDenshion;


class PauseScene : public Scene
{
public:
	static cocos2d::Scene* createScene();
	//auto slider;
	virtual bool init();
	CREATE_FUNC(PauseScene);
	void continuebuttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void againbuttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void menubuttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	//void sliderChange(Ref* psender, Control::EventType event);
};
#endif