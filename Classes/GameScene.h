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
	Player hero1 = ("Hero.png");//游戏中的玩家英雄
	std::map<cocos2d::EventKeyboard::KeyCode, bool>KeyMap;
	bool refreshMask;
	bool ifPress_S = false;

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual void update(float dt);
	//virtual void onEnter();
	//virtual void onEixt();

	//定义键盘操作的函数
	void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);//按下按键监视函数

	CREATE_FUNC(GameScene);
};

#endif __GAME_SCENE_H__