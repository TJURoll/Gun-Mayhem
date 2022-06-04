#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include"cocos2d.h"
#include"Player.h"
#include<map>

class GameScene : public cocos2d::Scene
{
private:
	cocos2d::Sprite* _play;
	cocos2d::TMXTiledMap* _tileMap;
	cocos2d::TMXLayer* _collidable1;
	cocos2d::TMXLayer* _collidable2;
	Hero1 hero1 = ("warlord-helmet.png");//��Ϸ�е����Ӣ��
	//int lastile = 0;
	//cocos2d::Sprite* tile[1000];
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