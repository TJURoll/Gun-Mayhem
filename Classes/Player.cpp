#include "Player.h"
#include"GameScene.h"

Hero1::Hero1(std::string urlOfPiture)
{
	hero = Sprite::create(urlOfPiture);
}


bool Player::whetherCanMove(const Vec2 position)
{
	/*用于判断此时精灵是否能够跳跃到此处*/
	return true;
}
