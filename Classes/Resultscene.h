#ifndef _RESULTSCENE_
#define _RESULTSCENE_
//��ʾ��Ϸ���ʤ������ʧ��
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace ui;

//�����ĳ���
class ResultScene : public Scene
{
private:
	void SwitchToStartScene(float);//�����л�����
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(ResultScene);
};

#endif