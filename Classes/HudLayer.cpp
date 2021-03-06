#include "HudLayer.h"
#include "InventoryManager.h"
#include "JoyStick.h"
#include "UserInterface.h"

using namespace cocos2d;

bool HudLayer::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	InventoryManager::GetInstance()->Init(this);
	JoyStick::GetInstance()->init(this);
	UserInterface::GetInstance()->init(this);
	this->scheduleUpdate();

	return true;
}

void HudLayer::update(float delta)
{
	InventoryManager::GetInstance()->Update(delta);
	JoyStick::GetInstance()->update(delta);
	UserInterface::GetInstance()->update(delta);
}