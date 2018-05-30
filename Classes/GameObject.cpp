#include "GameObject.h"

#include "GameObjectManager.h"

USING_NS_CC;

int GameObject::idCounter = 0;

GameObject::GameObject() : id(idCounter++), position(0, 0), direction(1, 0),
scale(1, 1), active(true), sprite(nullptr)
{
	GameObjectManager::GetInstance()->AddGameObject(this);
}

GameObject::~GameObject()
{
	//GameObjectManager::GetInstance()->RemoveGameObject(this->id);
}

void GameObject::SetSprite(std::string filename, std::string name)
{
	spriteNode = cocos2d::Node::create();
	spriteNode->setName(name);
	
	sprite = Sprite::create(filename);
	sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setPosition(0, 0);
	sprite->setName(name+"sprite");

	spriteNode->addChild(sprite, 1);

	//TODO: Send sprite node to scene


	//setting the physics body
	physicsBody = PhysicsBody::createBox(Size(sprite->getContentSize().width, sprite->getContentSize().height), PhysicsMaterial(0.0f, 0.0f, 1.f));
	sprite->addComponent(physicsBody);
}

void GameObject::SetAnimFrames(Vector<SpriteFrame*> spriteFrameList, float delay)
{
	Animation* animation = Animation::createWithSpriteFrames(animFrames, delay);
	animate = Animate::create(animation);
	animate->retain();
}

void GameObject::Destroy()
{
	this->isDone = true;
}

bool GameObject::isDead()
{
	return this->isDone;
}
