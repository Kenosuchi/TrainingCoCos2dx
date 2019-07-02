#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Enemy
{
public:
	Enemy();
	~Enemy();

	bool init(Vec2 position);
	void update(float dt);
	void createAnimation();
	void runAnimation();
	Sprite* getSprite() { return _sprite; }
	bool getIsDetroy() { return isDetroy; }
private:
	Sprite* _sprite;
	Animate* animate;

	bool isDetroy;
};

