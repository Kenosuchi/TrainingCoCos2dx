#include "Bullet.h"

Bullet::Bullet()
{
	_velocity = Vec2(0, 0);
	isOutOfRange = false;
}


Bullet::~Bullet()
{
}

bool Bullet::init(Vec2 position,Vec2 Direction)
{
	_sprite = Sprite::create("player_bullet.png");
	_sprite->setPosition(position.x, position.y);
	_speed = 2000;
	_velocity = Direction*_speed;

	auto bodyWall = PhysicsBody::createBox(Size(_sprite->getContentSize().width, _sprite->getContentSize().height));
	bodyWall->getShape(0)->setRestitution(0.8f);
	bodyWall->getShape(0)->setFriction(1.0f);
	bodyWall->getShape(0)->setDensity(1.0f);
	bodyWall->setDynamic(false);
	bodyWall->setContactTestBitmask(0x00000001);
	//bodyWall->setTag();
	_sprite->setPhysicsBody(bodyWall);
	_sprite->setTag(1);
	return true;
}

void Bullet::update(float dt)
{
	if (_sprite == NULL)
		return;
	Vec2 position = _sprite->getPosition();

	position += _velocity*dt;

	if (position.y > _Range.height)
		isOutOfRange = true;

	_sprite->setPosition(position);
}
