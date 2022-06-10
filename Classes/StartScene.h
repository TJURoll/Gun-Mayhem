#ifndef _STARTSCENE_
#define _STARTSCENE_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/SimpleAudioEngine.h"

using namespace cocos2d;
using namespace ui;
typedef void (*pFunc)(Ref*, Widget::TouchEventType);


class StartScene : public Scene
{
private:
	//按钮创建函数
	Button* buttonCreate(std::string titleText,pFunc switchSceneEvent);

	//添加按钮到界面上
	void buttonAdd(std::vector<Button*> buttonList);
public:
	virtual bool init();
	CREATE_FUNC(StartScene);
};
#endif