#include "Player.h"

Player::Player(std::string urlOfSpirite):Entity(urlOfSpirite){}

Animation* Player::removeRight()
{
	return nullptr;
}

Animation* Player::removeLeft()
{
	return nullptr;
}

Animation* Player::attack(Entity* entity)
{
	return nullptr;
}

Animation* Player::getHurt(int hurtValue)
{
	return nullptr;
}

void Player::changeTexture(const bool direction)
{
	sprite->setFlippedX(direction);
	dynamic_cast<Sprite*>(sprite->getChildByName("gun"))->setFlippedX(direction);//·­×ªÇ¹Ðµ
}
