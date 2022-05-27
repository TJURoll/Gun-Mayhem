#ifndef _STARTSCENE_
#define _STARTSCENE_
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace ui;
typedef void (*pFunc)(Ref*, Widget::TouchEventType);
class StartScene : public Scene
{
private:
	Size visibleSize;
	Vec2 origin;
	Button* buttonCreate(std::string titleText,pFunc switchSceneEvent);
	void buttonAdd(std::vector<Button*> buttonList);
public:
	StartScene();

	virtual bool init();

	CREATE_FUNC(StartScene);
};
#endif