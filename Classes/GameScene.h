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
	Player hero1 = ("Hero.png");//��Ϸ�е����Ӣ��
	Monster monster1 = ("monster.png");//��Ϸ�еĹ���1
	Monster monster2 = ("monster2.png");//��Ϸ�еĹ���2

	std::map<cocos2d::EventKeyboard::KeyCode, bool>KeyMap;
	EventListenerMouse* _mouseListener;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual void update(float dt);
	//virtual void onEnter();
	//virtual void onEixt();


	//void setPlayerPosition(cocos2d::Vec2 position);//�˺����������þ���λ�ã���⾫���Ƿ����ϰ�����ײ
	//cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);//�����������ת���ɵ�ͼ��Ƭ�����

private:
	//������̲����ĺ���
	void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);//���°������Ӻ���

	//��������
	void dropWeapons();

	//dropWeapons�еĺ���
	void addBoxes(const float ft);

	//���ñ߽�ı�������
	void setGroundBitMasks(Node* node);

	//������Ӵ��ļ�������ӵ�����
	void addContactListener();

	//�����������ǹ�е�һ��
	Gun* randomGun();

	void timeUpdate(float ft);
	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};

#endif __GAME_SCENE_H__