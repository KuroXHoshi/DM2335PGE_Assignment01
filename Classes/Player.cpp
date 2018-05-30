#include "Player.h"
USING_NS_CC;

Player::Player()
{
	this->SetSprite("Blue_Front1.png", "Player");

	//auto listener = EventListenerKeyboard::create();
	//listener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);
	//listener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);
	
	kbListener = EventListenerKeyboard::create();
	kbListener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);
	kbListener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);

	
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//Director::getInstance()->getRunningScene()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, spriteNode);

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(Player::onMousePressed, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(Player::onMouseReleased, this);
	//Director::getInstance()->getRunningScene()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, spriteNode);
}

void Player::Update(double dt)
{
}

void Player::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_W)
	{
		auto moveEvent = MoveBy::create(5.0f, Vec2(1000.0f, 0.f));
		sprite->runAction(moveEvent)->setTag(1);

		sprite->stopActionByTag(0);
		sprite->runAction(RepeatForever::create(animate))->setTag(0);
	}
	else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_S)
	{
		auto moveEvent = MoveBy::create(5.0f, Vec2(-1000.0f, 0.f));
		sprite->runAction(moveEvent)->setTag(1);

		sprite->stopActionByTag(0);
		sprite->runAction(RepeatForever::create(animate))->setTag(0);
	}
	else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_A)
	{
		auto moveEvent = MoveBy::create(5.0f, Vec2(-1000.0f, 0.f));
		sprite->runAction(moveEvent)->setTag(1);

		sprite->stopActionByTag(0);
		sprite->runAction(RepeatForever::create(animate))->setTag(0);
	}
	else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_D)
	{
		auto moveEvent = MoveBy::create(5.0f, Vec2(1000.0f, 0.f));
		sprite->runAction(moveEvent)->setTag(1);

		sprite->stopActionByTag(0);
		sprite->runAction(RepeatForever::create(animate))->setTag(0);
	}
}

void Player::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW || keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		sprite->stopActionByTag(1);
	}
}

void Player::onMousePressed(cocos2d::Event * event_)
{
}

void Player::onMouseReleased(cocos2d::Event * event_)
{
}

EventListenerKeyboard* Player::GetKbListener()
{
	return kbListener;
}
