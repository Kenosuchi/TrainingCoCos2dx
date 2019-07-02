#include "Player.h"
#include <math.h>
Player::Player()
{
}

Player::~Player()
{
}

bool Player::init(Size winSize,Scene*scene)
{	_velocity = Vec2(0, 0);
	_dir = Direction::none;
	_InitialPos = Vec2(winSize.width/2, winSize.height/8);
	_speed = 5000.0f;
	_sprite = Sprite::create("1.f0012.png");
	_sprite->setPosition(_InitialPos.x, _InitialPos.y);
	_sprite->setScale(0.8f);
	moveToPos = _InitialPos;

	createAnimation();
	runAnimation();

	//physic
	auto bodyWall = PhysicsBody::createBox(Size(_sprite->getContentSize().width,_sprite->getContentSize().height));
	bodyWall->getShape(0)->setRestitution(0.8f);
	bodyWall->getShape(0)->setFriction(1.0f);
	bodyWall->getShape(0)->setDensity(1.0f);
	bodyWall->setDynamic(false);
	bodyWall->setContactTestBitmask(0x00000001);

	_sprite->setPhysicsBody(bodyWall);
	_sprite->setTag(10);
	scene->addChild(_sprite, 2);

	m_fTimeSpawnBullet = 0.5f;
	CreateBullet(scene);
	haveItem = true;
	return true;
}

void Player::update(float dt,Scene* scene)
{
	makeDirection();
	move(dt);

	UpdateBullet(dt, scene);
}

void Player::CreateBullet(Scene * scene)
{
		Bullet*bullet = new Bullet();
		bullet->init(_sprite->getPosition(), Vec2(0, 1));
		scene->addChild(bullet->getSprite());
		m_vBullet.push_back(bullet);
}

void Player::CreateFiveBullet(Scene * scene)
{
	float dx, dy;
	int c = 1;
	for (int i = 0; i < 5; ++i) {
		float k = 0.2*i;
		
		Bullet*bullet = new Bullet();
		dx = 0.4 - k;
		dy = 1 - abs(dx);
		bullet->init(_sprite->getPosition(), Vec2(dx, dy));
		bullet->getSprite()->setRotation(45.0f - (i+1)*15.0f);
		scene->addChild(bullet->getSprite());
		m_vBullet.push_back(bullet);
	}
}

void Player::createAnimation()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plane.plist", "plane.png");

	const int numberSprite = 4;
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(numberSprite);

	for (int i = 0; i < 4; ++i) {
		std::string fileName = "1.f001"+std::to_string(i+2)+".png";
		animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName));
	}
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.15f);
	animate = Animate::create(animation);
}

void Player::runAnimation()
{
	_sprite->runAction(RepeatForever::create(animate));
}

void Player::move(float dt)
{
	Vec2 position = _sprite->getPosition();
	if (_dir == Direction::none) {
		position = moveToPos;
		_sprite->setPosition(position);
		return;
	}
	switch (_dir) {
	case Direction::left:
		_velocity.x -= _speed;
		break;
	case Direction::right:
		_velocity.x += _speed;
		break;
	case Direction::up:
		_velocity.y += _speed;
		break;
	case Direction::down:
		_velocity.y -= _speed;
		break;
	case Direction::leftup:
		_velocity.x -= _speed;
		_velocity.y += _speed;
		break;
	case Direction::leftdown:
		_velocity.x -= _speed;
		_velocity.y -= _speed;
		break;
	case Direction::rightup:
		_velocity.x += _speed;
		_velocity.y += _speed;
		break;
	case Direction::rightdown:
		_velocity.x += _speed;
		_velocity.y -= _speed;
		break;
	}

	position = _sprite->getPosition() + _velocity*dt;
	_sprite->setPosition(position);
	_velocity = Vec2(0, 0);
}

void Player::makeDirection()
{
	Vec2 offset = moveToPos - _sprite->getPosition();

	if (offset.x > 100) {
		if (offset.y > 100)
			_dir = Direction::rightup;
		else if (offset.y < -100)
			_dir = Direction::rightdown;
		else
			_dir = Direction::right;
	}
	else if (offset.x < -100) {
		if (offset.y > 100)
			_dir = Direction::leftup;
		else if (offset.y < -100)
			_dir = Direction::leftdown;
		else
			_dir = Direction::left;
	}
	else {
		if (offset.y > 100)
			_dir = Direction::up;
		else if (offset.y < -100)
			_dir = Direction::down;
		else
			_dir = Direction::none;
	}
}

void Player::UpdateBullet(float dt,Scene * scene)
{
	if (m_fTimeSpawnBullet < 0.0f) {
		for (int i = 0; i < m_vBullet.size(); ++i) {
			scene->removeChild(m_vBullet[i]->getSprite());
			delete m_vBullet[i];
		}
		m_vBullet.clear();
		m_fTimeSpawnBullet = 0.5f;
		if (!haveItem) {
			CreateBullet(scene);
		}
		else {
			CreateFiveBullet(scene);
		}
	}
	else {
		for (int i = 0; i < m_vBullet.size(); ++i) {
			if (m_vBullet[i]->getSprite()->getTag() != -1)
				m_vBullet[i]->update(dt);
			else {
				scene->removeChild(m_vBullet[i]->getSprite());
				delete m_vBullet[i];
				m_vBullet.erase(m_vBullet.begin() + i);
			}
		}
		m_fTimeSpawnBullet -= dt;
	}
	
}

