#include "UpgradeStone.h"

#include "InventoryManager.h"

UpgradeStone * UpgradeStone::GenerateStone(int modifier, cocos2d::Size size)
{
	UpgradeStone* newStone = new UpgradeStone();	
	newStone->type = (UPGRADE_TYPE)cocos2d::RandomHelper::random_int(0, UPGRADE_TYPE::UT_COUNT - 1);
	switch (newStone->type)
	{
	case UPGRADE_TYPE::UT_DAMAGE:
		newStone->btn = Button::create("textures/damage_stone.png");
		break;
	case UPGRADE_TYPE::UT_FIRERATE:
		newStone->btn = Button::create("textures/firerate_stone.png");
		break;
	case UPGRADE_TYPE::UT_RANGE:
		newStone->btn = Button::create("textures/range_stone.png");
		break;
	case UPGRADE_TYPE::UT_CRITCHANCE:
		newStone->btn = Button::create("textures/critical_chance_stone.png");
		break;
	case UPGRADE_TYPE::UT_CRITDAMAGE:
		newStone->btn = Button::create("textures/critical_damage_stone.png");
		break;
	}
	newStone->btn->setScaleX((size.width / newStone->btn->getContentSize().width));
	newStone->btn->setScaleY((size.width / newStone->btn->getContentSize().width));
	newStone->btn->retain();
	switch (newStone->type)
	{
	case UPGRADE_TYPE::UT_DAMAGE:
		newStone->modififyingValue = cocos2d::random(0.f, 1.f) * ((float)modifier / 5);
		break;
	case UPGRADE_TYPE::UT_FIRERATE:
		newStone->modififyingValue = cocos2d::random(0.f, 1.f) * ((float)modifier / 5);
		break;
	case UPGRADE_TYPE::UT_RANGE:
		newStone->modififyingValue = cocos2d::random(0.f, 1.f) * ((float)modifier / 5);
		break;
	case UPGRADE_TYPE::UT_CRITCHANCE:
		newStone->modififyingValue = cocos2d::random(0.f, 1.f) * ((float)modifier / 5);
		break;
	case UPGRADE_TYPE::UT_CRITDAMAGE:
		newStone->modififyingValue = cocos2d::random(0.f, 1.f) * ((float)modifier / 5);
		break;
	}
	return newStone;
}

void UpgradeStone::onClick(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		InventoryManager::GetInstance()->DisplayStoneStat(this);
	}
}
