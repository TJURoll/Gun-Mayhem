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
	//��ť��������
	Button* buttonCreate(std::string titleText,pFunc switchSceneEvent);

	//��Ӱ�ť��������
	void buttonAdd(std::vector<Button*> buttonList);
public:
	virtual bool init();
	CREATE_FUNC(StartScene);
};
#endif