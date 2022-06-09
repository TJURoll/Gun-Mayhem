#ifndef _RESULTSCENE_
#define _RESULTSCENE_
//显示游戏结果胜利或是失败
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace ui;

//结束的场景
class ResultScene : public Scene
{
private:
	void SwitchToStartScene(float);//场景切换函数
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(ResultScene);
};

#endif