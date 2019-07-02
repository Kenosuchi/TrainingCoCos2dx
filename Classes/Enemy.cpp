#include "Enemy.h"



Enemy::Enemy()
{
	isDetroy = false;
}


Enemy::~Enemy()
{
}

bool Enemy::init(Vec2 position)
{
	_sprite = Sprite::create("1.f0026.png");
	_sprite->setPosition(position.x, position.y);

	createAnimation();
	runAnimation();
	auto bodyWall = PhysicsBody::createCircle(_sprite->getContentSize().width / 3);
	bodyWall->getShape(0)->setRestitution(0.8f);
	bodyWall->getShape(0)->setFriction(1.0f);
	bodyWall->getShape(0)->setDensity(1.0f);
	bodyWall->setDynamic(false);
	bodyWall->setContactTestBitmask(0x00000001);

	_sprite->setPhysicsBody(bodyWall);
	_sprite->setTag(2);
	return true;
}

void Enemy::update(float dt)
{
	if (_sprite == NULL)
		isDetroy = true;
}

void Enemy::createAnimation()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy.plist", "enemy.png");

	const int numberSprite = 4;

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(numberSprite);

	for (int i = 0; i < 4; ++i) {
		std::string fileName = "1.f003" + std::to_string(i + 4) + ".png";
		animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName));
	}
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.18f);
	animate = Animate::create(animation);
}

void Enemy::runAnimation()
{
	_sprite->runAction(RepeatForever::create(animate));
}
