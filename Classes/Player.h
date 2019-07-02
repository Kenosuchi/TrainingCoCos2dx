#pragma once

#include "cocos2d.h"
#include "Bullet.h"
USING_NS_CC;

enum class Direction {
	none,
	left,
	right,
	up,
	down,
	leftup,
	leftdown,
	rightup,
	rightdown
};

class Player{
public:
	Player();
	~Player();

	bool init(Size winSize,Scene*scene);
	void update(float dt,Scene*scene);
	void CreateBullet(Scene * scene);
	void CreateFiveBullet(Scene * scene);
	//----------------------------------------------------------
	void createAnimation();
	void runAnimation();
	void move(float dt);
	void makeDirection();
	void UpdateBullet(float dt,Scene * scene);
	//----------------------------------------------------------
	void setPosition(Vec2 pos) { _sprite->setPosition(pos); }
	Vec2 getPosition() { return _sprite->getPosition(); }
	Sprite* getSprite() { return _sprite; }
	//----------------------------------------------------------
	Vec2 moveToPos;
private:
	Sprite *_sprite;
	Animate* animate;

	Direction _dir;
	Vec2 _velocity;

	Vec2 _InitialPos;
	float _speed;

	std::vector<Bullet*> m_vBullet;
	float m_fTimeSpawnBullet;
	bool haveItem;
};