#include "GameObject.h"

#include "GameObjectManager.h"
#include "SceneManager.h"

USING_NS_CC;

int GameObject::idCounter = 0;

GameObject::GameObject() : id(idCounter++), position(0, 0), direction(1, 0),
scale(1, 1), active(true), sprite(nullptr), spriteNode(nullptr), isDone(false),
hasStartedUpdate(false)
{
	GameObjectManager::GetInstance()->AddGameObject(this);
}

GameObject::~GameObject()
{
	//GameObjectManager::GetInstance()->RemoveGameObject(this->id);
	Director::getInstance()->getRunningScene()->removeChild(spriteNode, true);
	//physicsBody->release();
	//sprite->release();
	//animate->release();
	//spriteNode->release();
	//animFrames.clear();

	Scene* currScene = Director::getInstance()->getRunningScene();
	EventDispatcher* _eventDispatcher = currScene->getEventDispatcher();
	_eventDispatcher->removeEventListener(contactListener);
}

void GameObject::Update(double dt)
{

}

void GameObject::Start()
{
}

void GameObject::SetSprite(std::string filename, std::string name)
{
	spriteNode = Node::create();
	spriteNode->setName(name);
	
	sprite = Sprite::create(filename);
	sprite->setAnchorPoint(Vec2(0.5f,0.5f));
	sprite->setPosition(0, 0);
	sprite->setName(name+"sprite");

	sprite->retain();

	spriteNode->addChild(sprite, 1);

	// Send sprite node to scene
	SceneManager::GetInstance()->AddNodeToCurrentScene(spriteNode);
}

void GameObject::SetAnimFrames(Vector<SpriteFrame*> spriteFrameList, float delay)
{
	Animation* animation = Animation::createWithSpriteFrames(spriteFrameList, delay);
	animate = Animate::create(animation);
	animate->retain();
}

void GameObject::SetPhysics(bool isDynamic, cocos2d::Vec2 velocity, bool isGravityEnabled)
{
	//setting the physics body
	physicsBody = PhysicsBody::createBox(Size(sprite->getContentSize().width, sprite->getContentSize().height), PhysicsMaterial(0.0f, 0.0f, 1.f));
	physicsBody->setDynamic(isDynamic);
	physicsBody->setVelocity(velocity);
	physicsBody->setGravityEnable(isGravityEnabled);
	sprite->addComponent(physicsBody);
	physicsBody->getNode()->setUserData(this);

	//Set collision bitmask
	physicsBody->setCategoryBitmask(BITMASK_ENUM::BITMASK_EVERYTHING);
	physicsBody->setContactTestBitmask(BITMASK_ENUM::BITMASK_EVERYTHING);
	physicsBody->setCollisionBitmask(BITMASK_ENUM::BITMASK_EVERYTHING);
	physicsBody->setTag(TAGENUM::NONE);

	Scene* currScene = Director::getInstance()->getRunningScene();
	EventDispatcher* _eventDispatcher = currScene->getEventDispatcher();

	contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameObject::OnContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, currScene);
	
	
	
}

bool GameObject::OnContactBegin(cocos2d::PhysicsContact & contact)
{
	return true;
}

void GameObject::Destroy()
{
	this->isDone = true;
}

bool GameObject::isDead()
{
	return this->isDone;
}
