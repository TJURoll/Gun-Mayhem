#ifndef _ROOMSCENE_
#define _ROOMSCENE_
#include "cocos2d.h"
#include "ui/CocosGUI.h"


using namespace cocos2d;
using namespace ui;

class RoomScene : public Scene
{
private:
	int AInum=1;//初始默认一个
public:
	void setAInum(int num);
	static cocos2d::Scene* createScene();
	virtual bool init();
	void buttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void ContinuebuttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	CREATE_FUNC(RoomScene);
};
#endif