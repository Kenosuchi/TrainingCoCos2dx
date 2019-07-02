#include "GameScene.h"

#define TAG_PLAYERBULLET 1;
#define ENEMY 2;


Scene * GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	Vect gravity(0.0f, 0.0f);
	scene->getPhysicsWorld()->setGravity(gravity);
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	_visibleSize = Director::getInstance()->getVisibleSize();
	_origin = Director::getInstance()->getVisibleOrigin();

	// Background
	auto backGround = Sprite::create("background-2.jpg");
	backGround->setAnchorPoint(Vec2(0.5, 0.5));
	backGround->setPosition(_visibleSize.width/2, _visibleSize.height/2);
	backGround->setScale(0.8f);
	this->addChild(backGround);
	//Player
	_player = new Player();
	_player->init(_visibleSize,this);
	//this->addChild(_player->getSprite(), 2);
	this->scheduleUpdate();
	//Enemy
	for (int i = 0; i < 4; ++i) {
		Vec2 position = Vec2(_visibleSize.width - 150, _visibleSize.height/2 + i*100);
		for (int j = 0; j < 8; ++j) {
			Enemy *enemy = new Enemy();
			float k = j * 150;
			enemy->init(Vec2(position.x -k, position.y));
			this->addChild(enemy->getSprite());
			_enemyList.push_back(enemy);
		}
	}

	//Physics world
	auto spWall = Sprite::create();
	spWall->setPosition(Point(_visibleSize.width / 2, _visibleSize.height / 2));
	auto bodyWall = PhysicsBody::createEdgeBox(_visibleSize,
		PHYSICSBODY_MATERIAL_DEFAULT, 2);
	bodyWall->getShape(0)->setRestitution(0.8f);
	bodyWall->getShape(0)->setFriction(1.0f);
	bodyWall->getShape(0)->setDensity(1.0f);
	bodyWall->setDynamic(false);
	bodyWall->setContactTestBitmask(0x00000001);
	spWall->setPhysicsBody(bodyWall);
	spWall->setTag(0);
	this->addChild(spWall);
	

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener,this);

	//Event
	auto eventListener = EventListenerTouchOneByOne::create();
	eventListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);

	return true;
}

void GameScene::update(float dt)
{
	_player->update(dt,this);
	
	for (int i = 0; i < _enemyList.size(); ++i) {
		if (_enemyList[i]->getSprite()->getTag() == -1) {
			this->removeChild(_enemyList[i]->getSprite());
			delete _enemyList[i];
			_enemyList.erase(_enemyList.begin() + i);
		}
		else
		_enemyList[i]->update(dt);
	}
	
}

bool GameScene::onTouchBegan(Touch * touch, Event * unused_event)
{
	Vec2 touchPos = Vec2(touch->getLocationInView().x, _visibleSize.height - touch->getLocationInView().y);
	_player->moveToPos = touchPos;
	return true;
}

bool GameScene::onContactBegan(PhysicsContact & contact)
{
	Sprite * a = (Sprite*)contact.getShapeA()->getBody()->getNode();
	Sprite * b = (Sprite*)contact.getShapeB()->getBody()->getNode();
	if (a == NULL || b == NULL)
		return true;

	if ((a->getTag() == 1 && b->getTag() == 2) || (a->getTag() == 2 && b->getTag() == 1)) {
		a->setTag(-1);
		b->setTag(-1);
	}
	else if ((a->getTag() == 1 && b->getTag() == 10) || (a->getTag() == 10 && b->getTag() == 1)) {
		return false;
	}
	return true;
	
}
