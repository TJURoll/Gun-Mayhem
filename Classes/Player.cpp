#include "Player.h"
#include"GameScene.h"

Hero1::Hero1(std::string urlOfPiture)
{
	hero = Sprite::create(urlOfPiture);
}


bool Player::whetherCanMove(const Vec2 position)
{
	/*�����жϴ�ʱ�����Ƿ��ܹ���Ծ���˴�*/
	return true;
}
