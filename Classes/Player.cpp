#include "Player.h"
#include "InventoryManager.h"
#include "JoyStick.h"
#include "WeaponGenerator.h"
#include "GameController.h"
#include "Enemy.h"
USING_NS_CC;


Player::Player()
{
	audio = CocosDenshion::SimpleAudioEngine::getInstance();
	factionTag = TAGENUM::PLAYER;
	weapon = nullptr;
	health = 1000;
	
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
	if (sprite->getNumberOfRunningActionsByTag(0) && !anyKeyHeld() && sprite->getName() == "Playersprite")
	{
		sprite->stopAllActions();
		sprite->setTexture("textures/player_1.tga");
	}
	//physicsBody->onAdd(); // bandaid fix for animation
	//physicsBody->setVelocity(Vec2::ZERO);

	this->position = sprite->getPosition();

	//Set weapons multiplier;
	if (weapon != nullptr)
	{
		float dmgmul = 1.0f;
		float attspdmul = 1.0f;
		float rangemul = 1.0f;
		float critchancemul = 1.0f;
		float critdmgmul = 1.0f;
		int num = stoneModifierSize;
		for (int i = 0; i < num; ++i)
		{
			UpgradeStone* us = stoneModifiers[i];
			if (us == nullptr)
				continue;
			switch (us->type)
			{
			case UpgradeStone::UPGRADE_TYPE::UT_FIRERATE:
				attspdmul += us->modififyingValue;
				break;
			case UpgradeStone::UT_DAMAGE:
				dmgmul += us->modififyingValue;
				break;
			case UpgradeStone::UT_RANGE:
				rangemul += us->modififyingValue;
				break;
			case UpgradeStone::UT_CRITCHANCE:
				critchancemul += us->modififyingValue;
				break;
			case UpgradeStone::UT_CRITDAMAGE:
				critdmgmul += us->modififyingValue;
				break;
			}
		}
		weapon->damageMultiplier = dmgmul;
		weapon->attackSpeedMultiplier = attspdmul;
		weapon->rangeMultiplier = rangemul;
		weapon->critChanceMultiplier = critchancemul;
		weapon->critDamageMultiplier = critdmgmul;
	}

	//sort gamecontroller enemy vector base on distance
	std::sort(GameController::GetInstance()->activeEnemies.begin(), GameController::GetInstance()->activeEnemies.end(), [this](const GameObject* a, const GameObject* b) -> bool {
		float aDist = (-this->position + a->position).lengthSquared();
		float bDist = (-this->position + b->position).lengthSquared();
		//DBOUT("aDist " << aDist << "   bDist " << bDist);
		return aDist < bDist;
	});

}

void Player::Start()
{
	this->SetSprite("textures/player_1.tga", "Player");
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));
	this->sprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	this->sprite->runAction(RepeatForever::create(this->animate))->setTag(0);

	weapon = WeaponGenerator::GetInstance()->GetWeapon(WEAPON_TYPES::FLAMETHROWER, 0);

	physicsBody = PhysicsBody::createCircle(sprite->getContentSize().width, PhysicsMaterial(0.0f, 0.0f, 1.f));
	SetPhysics(false, Vec2(0, 0), false);
	physicsBody->setVelocityLimit(100);
	//physicsBody->setRotationOffset(4);
	physicsBody->setRotationEnable(false);
	this->physicsBody->setCategoryBitmask(BITMASK_ENUM::BITMASK_PLAYER);
	this->physicsBody->setContactTestBitmask(BITMASK_ENUM::BITMASK_ENEMY + BITMASK_ENUM::BITMASK_ENEMY_BULLET);
	this->physicsBody->setCollisionBitmask(BITMASK_ENUM::BITMASK_ENEMY + BITMASK_ENUM::BITMASK_ENEMY_BULLET);
	
	InventoryManager::GetInstance()->AttachPlayer(this);
	JoyStick::GetInstance()->AttachPlayer(this);
	//this->physicsBody->setMass(1000.0f);
}

void Player::LookAt(Vec2 target_)
{
	//physicsBody->()
	if (!sprite)
		return;
	//sprite->setRotation(-90 + atan2(target_.y,target_.x) * 180 / 3.14159265f);
	sprite->setRotation(atan2(target_.x, target_.y) * 180 / 3.14159265f);
	//physicsBody->setRotationOffset(sprite->getRotation());
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
		//if (weapon != nullptr)
		//{
		//	audio->playEffect("sounds/shoot.mp3");
		//	//aka screem size
		//	auto visibleSize = Director::getInstance()->getVisibleSize();

		//	weapon->position.set(sprite->getPosition());
		//	weapon->direction.set(e->getCursorX() - visibleSize.width * 0.5f, e->getCursorY() - visibleSize.height * 0.5f);
		//	weapon->direction.normalize();

		//	weapon->Discharge();

		//}

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
	//LookAt(eventMouse->getLocation() - Director::getInstance()->getVisibleSize() * 0.5f);
}

EventListenerKeyboard* Player::GetKbListener()
{
	return kbListener;
}

EventListenerMouse * Player::GetMouseListener()
{
	return mouseListener;
}


void Player::FireWeapon(Vec2 target_)
{
	if (weapon != nullptr)
	{
		audio->playEffect("sounds/shoot.mp3");
		//aka screem size
		auto visibleSize = Director::getInstance()->getVisibleSize();

		weapon->position.set(sprite->getPosition());
		weapon->direction.set(target_.x, target_.y);
		weapon->direction.normalize();

		weapon->Discharge();

	}
}
