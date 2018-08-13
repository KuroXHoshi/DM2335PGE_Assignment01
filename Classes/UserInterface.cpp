#include "UserInterface.h"

UserInterface* UserInterface::instance = nullptr;

UserInterface* UserInterface::GetInstance()
{
	if (!instance)
	{
		instance = new UserInterface();
	}

	return instance;
}

void UserInterface::init(cocos2d::Layer* layer)
{
	MaxScale = 2.5f;

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));
	hudLayer = layer;

	HealthBar = Node::create();
	HealthBar->setName("PlayerHealthBar");

	HealthBarSprite = Sprite::create("textures/ui_healthbar1.tga");
	HealthBarSprite->setAnchorPoint(Vec2(0.f, 0.5f));
	HealthBarSprite->setPosition(Vec2(visibleSize.width * 0.05f, visibleSize.height * 0.9f));
	HealthBarSprite->setName(HealthBar->getName() + "Sprite");
	HealthBarSprite->setScaleX(MaxScale);
	HealthBarSprite->setScaleY(0.2f);
	HealthBarSprite->retain();
	HealthBar->addChild(HealthBarSprite);

	layer->addChild(HealthBar);
}

void UserInterface::update(float dt)
{
	if (player->GetHealth() <= 0)
	{
		HealthBarSprite->setScaleX(0.f);
		return;
	}

	float curHealthPercent = MaxScale * (player->GetHealth() / MaxPlayerHP);
	HealthBarSprite->setScaleX(curHealthPercent);
}

void UserInterface::AttachPlayer(Player* _input)
{
	player = _input;
	MaxPlayerHP = player->GetHealth();
}