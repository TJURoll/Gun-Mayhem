#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include"cocos2d.h"
#include"Player.h"
#include "Weapon.h"
#include<map>

class GameScene : public cocos2d::Scene
{
private:
	const float MASS = 10.f;
	Player hero1 = ("Hero.png");//��Ϸ�е����Ӣ��
	std::map<cocos2d::EventKeyboard::KeyCode, bool>KeyMap;
	bool refreshMask;
	bool ifPress_S = false;

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual void update(float dt);
	//virtual void onEnter();
	//virtual void onEixt();

	//������̲����ĺ���
	void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);//���°������Ӻ���

	CREATE_FUNC(GameScene);
};

#endif __GAME_SCENE_H__