#include "GameObject.h"

USING_NS_CC;

int GameObject::idCounter = 0;

GameObject::GameObject() : id(idCounter++), position(0, 0), direction(1, 0),
scale(1, 1), active(true), sprite(nullptr), spriteNode(nullptr)
{

}

void GameObject::SetSprite(std::string filename, std::string name)
{
	spriteNode = Node::create();
	spriteNode->setName(name);
	
	sprite = Sprite::create(filename);
	sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setPosition(0, 0);
	sprite->setName(name+"sprite");

	spriteNode->addChild(sprite, 1);

	//TODO: Send sprite node to scene


	//setting the physics body
	physicsBody = PhysicsBody::createBox(Size(sprite->getContentSize().width, sprite->getContentSize().height), PhysicsMaterial(0.0f, 0.0f, 1.f));
	//sprite->addComponent(physicsBody);
}

void GameObject::SetAnimFrames(Vector<SpriteFrame*> spriteFrameList, float delay)
{
	Animation* animation = Animation::createWithSpriteFrames(spriteFrameList, delay);
	animate = Animate::create(animation);
	animate->retain();
}
