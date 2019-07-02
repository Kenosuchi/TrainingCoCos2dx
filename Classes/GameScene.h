#pragma once

#include "cocos2d.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include <vector>
USING_NS_CC;
class GameScene:public Scene
{
public:
	static Scene* createScene();

	bool init();
	void update(float dt) override;

	bool onTouchBegan(Touch* touch, Event* unused_event);
	bool onContactBegan(PhysicsContact& contact);
	CREATE_FUNC(GameScene);
private:
	Player	*_player;

	std::vector<Enemy*> _enemyList;
	Size _visibleSize;
	Vec2 _origin;
};

