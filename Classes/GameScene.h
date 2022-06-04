#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include"cocos2d.h"
#include"Player.h"
#include<map>

class GameScene : public cocos2d::Scene
{
private:
	Player hero1 = ("Hero.png");//游戏中的玩家英雄
	std::map<cocos2d::EventKeyboard::KeyCode, bool>KeyMap;


public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual void update(float dt);
	//virtual void onEnter();
	//virtual void onEixt();



	//void setPlayerPosition(cocos2d::Vec2 position);//此函数重新设置精灵位置，检测精灵是否与障碍物碰撞
	//cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);//把像素坐标点转换成地图瓦片坐标点

	//定义键盘操作的函数
	void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);//按下按键监视函数
	void onMouseDown(Event* event);//按下鼠标动作监视函数
	//定义鼠标操作的函数


	// a selector callback
	//void buttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type);将此句删除

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};

#endif __GAME_SCENE_H__