#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Weapon.h"
#include "Entity.h"
#include "Monster.h"
#include "PauseScene.h"
#include "ResultScene.h"
#include "Global.h"
#include "MyTime.h"
#include "editor-support/cocostudio/SimpleAudioEngine.h"

class GameScene : public cocos2d::Scene
{
private:
	static constexpr float MASS = 10.0f;
	Player hero1 = ("Hero.png");//游戏中的玩家英雄
	Monster monster1 = ("monster.png");//游戏中的怪物1
	Monster monster2 = ("monster2.png");//游戏中的怪物2

	std::map<cocos2d::EventKeyboard::KeyCode, bool>KeyMap;
	EventListenerMouse* _mouseListener;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual void update(float dt);
	//virtual void onEnter();
	//virtual void onEixt();


	//void setPlayerPosition(cocos2d::Vec2 position);//此函数重新设置精灵位置，检测精灵是否与障碍物碰撞
	//cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);//把像素坐标点转换成地图瓦片坐标点

private:
	//定义键盘操作的函数
	void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);//按下按键监视函数

	//掉落武器
	void dropWeapons();

	//dropWeapons中的函数
	void addBoxes(const float ft);

	//设置边界的比特掩码
	void setGroundBitMasks(Node* node);

	//将物理接触的监听器添加到场景
	void addContactListener();

	//随机生成三种枪中的一个
	Gun* randomGun();

	void timeUpdate(float ft);
	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};

#endif __GAME_SCENE_H__