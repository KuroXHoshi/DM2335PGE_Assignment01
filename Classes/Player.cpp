#include "Player.h"
USING_NS_CC;

Player::Player()
{
	this->SetSprite("textures/player_1.tga", "Player");
	factionTag = TAGENUM::PLAYER;
	weapon = new Weapon();
	health = 1000;
	weapon->Set(10, 20, 1, 0, 1000, 0, "textures/Protagonist_Bullet.tga");
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
		//physicsBody->applyForce(Vec2(0, 10000) * dt);
		auto moveEvent = MoveBy::create(0.0f, Vec2(0.0f, 100.f) * dt);
		sprite->runAction(moveEvent)->setTag(1);
		
		//sprite->stopActionByTag(0);
		if (!sprite->getNumberOfRunningActionsByTag(0))
		sprite->runAction(RepeatForever::create(animate))->setTag(0);
	}
	if (isKeyHeld(EventKeyboard::KeyCode::KEY_S))
	{
		//physicsBody->applyForce(Vec2(0, -10000) * dt);
		auto moveEvent = MoveBy::create(0.0f, Vec2(0.0f, -100.f) * dt);
		sprite->runAction(moveEvent)->setTag(1);

		//sprite->stopActionByTag(0);
		if (!sprite->getNumberOfRunningActionsByTag(0))
		sprite->runAction(RepeatForever::create(animate))->setTag(0);
	}
	if (isKeyHeld(EventKeyboard::KeyCode::KEY_A))
	{
		//physicsBody->applyForce(Vec2(-10000, 0) * dt);
		auto moveEvent = MoveBy::create(0.0f, Vec2(-100.0f, 0.f) * dt);
		sprite->runAction(moveEvent)->setTag(1);

		//sprite->stopActionByTag(0);
		if (!sprite->getNumberOfRunningActionsByTag(0))
		sprite->runAction(RepeatForever::create(animate))->setTag(0);
	}
	if (isKeyHeld(EventKeyboard::KeyCode::KEY_D))
	{
		//physicsBody->applyForce(Vec2(10000, 0) * dt);
		auto moveEvent = MoveBy::create(0.0f, Vec2(100.0f, 0.f) * dt);
		sprite->runAction(moveEvent)->setTag(1);

		//sprite->stopActionByTag(0);
		if (!sprite->getNumberOfRunningActionsByTag(0))
		sprite->runAction(RepeatForever::create(animate))->setTag(0);
	}
	if (sprite->getNumberOfRunningActionsByTag(0) && !anyKeyHeld())
	{
		sprite->stopAllActions();
		sprite->setTexture("textures/player_1.tga");
	}
	physicsBody->onAdd(); // bandaid fix for animation
}

void Player::Start()
{
	physicsBody = PhysicsBody::createCircle(sprite->getContentSize().width, PhysicsMaterial(0.0f, 0.0f, 1.f));
	SetPhysics(true, Vec2(0, 0), false);
	physicsBody->setVelocityLimit(100);
	//physicsBody->setRotationOffset(4);
	physicsBody->setRotationEnable(false);
	this->physicsBody->setCategoryBitmask(BITMASK_ENUM::BITMASK_PLAYER);
	this->physicsBody->setContactTestBitmask(BITMASK_ENUM::BITMASK_ENEMY + BITMASK_ENUM::BITMASK_ENEMY_BULLET);
	this->physicsBody->setCollisionBitmask(BITMASK_ENUM::BITMASK_ENEMY + BITMASK_ENUM::BITMASK_ENEMY_BULLET);
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
	EventMouse* e = (EventMouse*)event_;
	if (e->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
	{
		//aka screem size
		auto visibleSize = Director::getInstance()->getVisibleSize();

		weapon->position.set(sprite->getPosition());
		weapon->direction.set(e->getCursorX() - visibleSize.width * 0.5f, e->getCursorY() - visibleSize.height * 0.5f);
		weapon->direction.normalize();
		
		weapon->Discharge();
	}
}

void Player::onMouseReleased(cocos2d::Event * event_)
{
	EventMouse* e = (EventMouse*)event_;
	if (e->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
	{
		/*auto curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
		curSprite->stopActionByTag(1);
		int displacement = e->getCursorX() - curSprite->getPositionX();

		auto moveEvent = MoveBy::create(abs(displacement) / 300.0f, Vec2(displacement, 0));

		auto callbackStop = CallFunc::create([curSprite]() {
			curSprite->stopAllActions();
			curSprite->runAction(RepeatForever::create(animateIdle))->setTag(0);
		});

		auto seq = Sequence::create(moveEvent, callbackStop, nullptr);

		curSprite->runAction(seq)->setTag(1);

		curSprite->stopActionByTag(0);
		curSprite->runAction(RepeatForever::create(animateMouse))->setTag(0);*/
	}
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
