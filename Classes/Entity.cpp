#include "Entity.h"

Sprite* Entity::getSprite()
{
	return sprite;
}

bool Entity::whetherCanMove(const Vec2 position)
{
	return true;
}

void Entity::bindSpirite(Sprite* _sprite)
{
	if(sprite!=nullptr)
		sprite->removeFromParentAndCleanup(true);

	sprite = _sprite;
}

bool Entity::getDirection(void)
{
	return direction;
}

void Entity::changeDirection(const bool I_direction)
{
	direction = I_direction;
}

Entity::Entity(std::string url){
	lifeNum = 0;
	auto pinfo = AutoPolygon::generatePolygon(url);

	sprite=Sprite::create(pinfo);
}//初始化参数列表


