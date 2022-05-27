#pragma once
#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include"Player.h"
using namespace cocos2d;
using namespace ui;
class GameScene : public Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void putBarrier(Sprite* barrier, const Vec2 position, float scaleRate);//���ڷ����ϰ��ﾫ��
	void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);//���°��¼����Ӻ���
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);//���°��ؼ����Ӻ���
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap;//��һ��map�������ʱ�û��Ƿ��¼���
	void onMouseDown(Event* event);//������궯�����Ӻ���
	void update(float delta);//���ڸ��°���״̬
	void jumpTo(Hero1* hero,int height);//����ʵ�ָ�Ӣ�۵���Ծ����

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
private:
	Hero1 hero1 = ("warlord-helmet.png");//��Ϸ�е����Ӣ��
};
#endif
