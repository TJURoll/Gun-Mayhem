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
	void putBarrier(Sprite* barrier, const Vec2 position, float scaleRate);//用于放置障碍物精灵
	void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);//按下按下键监视函数
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);//按下按回键监视函数
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap;//用一个map来储存此时用户是否按下键盘
	void onMouseDown(Event* event);//按下鼠标动作监视函数
	void update(float delta);//用于更新按键状态
	void jumpTo(Hero1* hero,int height);//用于实现该英雄的跳跃功能

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
private:
	Hero1 hero1 = ("warlord-helmet.png");//游戏中的玩家英雄
};
#endif
