#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include"cocos2d.h"
#include"Player.h"
#include<map>

class GameScene : public cocos2d::Scene
{
private:
	Player hero1 = ("Hero.png");//��Ϸ�е����Ӣ��
	std::map<cocos2d::EventKeyboard::KeyCode, bool>KeyMap;


public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual void update(float dt);
	//virtual void onEnter();
	//virtual void onEixt();



	//void setPlayerPosition(cocos2d::Vec2 position);//�˺����������þ���λ�ã���⾫���Ƿ����ϰ�����ײ
	//cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);//�����������ת���ɵ�ͼ��Ƭ�����

	//������̲����ĺ���
	void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);//���°������Ӻ���
	void onMouseDown(Event* event);//������궯�����Ӻ���
	//�����������ĺ���


	// a selector callback
	//void buttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type);���˾�ɾ��

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};

#endif __GAME_SCENE_H__