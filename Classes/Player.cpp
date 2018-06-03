#include "Player.h"
USING_NS_CC;

Player::Player()
{
	this->SetSprite("textures/player_1.tga", "Player");
	
	//auto listener = EventListenerKeyboard::create();
	//listener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);
	//listener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);
	
	kbListener = EventListenerKeyboard::create();
	kbListener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);
	kbListener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);
	
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//Director::getInstance()->getRunningScene()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, spriteNode);

	mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(Player::onMousePressed, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(Player::onMouseReleased, this);
	mouseListener->onMouseMove = CC_CALLBACK_1(Player::onMouseMove, this);
	//Director::getInstance()->getRunningScene()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, spriteNode);
}

void Player::Update(double dt)
{
	if (isKeyHeld(EventKeyboard::KeyCode::KEY_W))
	{
		physicsBody->applyForce(Vec2(0, 10000) * dt);
	}
	if (isKeyHeld(EventKeyboard::KeyCode::KEY_S))
	{
		physicsBody->applyForce(Vec2(0, -10000) * dt);
	}
	if (isKeyHeld(EventKeyboard::KeyCode::KEY_A))
	{
		physicsBody->applyForce(Vec2(-10000, 0) * dt);
	}
	if (isKeyHeld(EventKeyboard::KeyCode::KEY_D))
	{
		physicsBody->applyForce(Vec2(10000, 0) * dt);
	}
	physicsBody->onAdd(); // bandaid fix for animation
	//if ()
}

void Player::Start()
{
	physicsBody = PhysicsBody::createCircle(sprite->getContentSize().width, PhysicsMaterial(0.0f, 0.0f, 1.f));
	SetPhysics(true, Vec2(0, 0), false);
	physicsBody->setVelocityLimit(100);
	//physicsBody->setRotationOffset(4);
}

void Player::LookAt(Vec2 target_)
{
	//physicsBody->(-90 + atan2(target_.y, target_.x) * 180 / 3.14159265f);
	sprite->setRotation(-90 + atan2(target_.y,target_.x) * 180 / 3.14159265f);
}

//void Player::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
//{
//	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_W)
//	{
//		/*auto moveEvent = MoveBy::create(5.0f, Vec2(1000.0f, 0.f));
//		sprite->runAction(moveEvent)->setTag(1);
//
//		sprite->stopActionByTag(0);
//		sprite->runAction(RepeatForever::create(animate))->setTag(0);*/
//		physicsBody->applyForce(Vec2(0, 10));
//	}
//	else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_S)
//	{
//		auto moveEvent = MoveBy::create(5.0f, Vec2(-1000.0f, 0.f));
//		sprite->runAction(moveEvent)->setTag(1);
//
//		sprite->stopActionByTag(0);
//		sprite->runAction(RepeatForever::create(animate))->setTag(0);
//	}
//	else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_A)
//	{
//		auto moveEvent = MoveBy::create(5.0f, Vec2(-1000.0f, 0.f));
//		sprite->runAction(moveEvent)->setTag(1);
//
//		sprite->stopActionByTag(0);
//		sprite->runAction(RepeatForever::create(animate))->setTag(0);
//	}
//	else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_D)
//	{
//		auto moveEvent = MoveBy::create(5.0f, Vec2(1000.0f, 0.f));
//		sprite->runAction(moveEvent)->setTag(1);
//
//		sprite->stopActionByTag(0);
//		sprite->runAction(RepeatForever::create(animate))->setTag(0);
//	}
//}

//void Player::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
//{
//	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW || keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
//	{
//		sprite->stopActionByTag(1);
//	}
//}

void Player::onMousePressed(cocos2d::Event * event_)
{
}

void Player::onMouseReleased(cocos2d::Event * event_)
{
}

void Player::onMouseMove(cocos2d::Event * event_)
{
	EventMouse* eventMouse = (EventMouse*)event_;
	LookAt(eventMouse->getLocation() - Director::getInstance()->getVisibleSize() * 0.5f);
}

EventListenerKeyboard* Player::GetKbListener()
{
	return kbListener;
}

EventListenerMouse * Player::GetMouseListener()
{
	return mouseListener;
}
