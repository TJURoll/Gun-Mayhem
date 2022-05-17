#ifndef _STARTSCENE_
#define _STARTSCENE_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;
class StartScene : public Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void buttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type);

	// implement the "static create()" method manually
	CREATE_FUNC(StartScene);
	//private:
	   // Button* ButtonCreate(const char* text)
};
#endif