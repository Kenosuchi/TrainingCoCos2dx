#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Bullet
{
public:
	Bullet();
	~Bullet();

	bool init(Vec2 position,Vec2 Direction);
	void update(float dt);

	Sprite* getSprite() { return _sprite; }

	bool isOutOfRange;
private:
	Sprite* _sprite;
	Vec2 _velocity;
	Size _Range;
	
	float _speed;
};

