#include "UpgradeStone.h"

#include "InventoryManager.h"

UpgradeStone * UpgradeStone::GenerateStone(int modifier, cocos2d::Size size)
{
	UpgradeStone* newStone = new UpgradeStone();
	newStone->btn = Button::create("Blue_Front1.png");
	newStone->btn->setContentSize(size);
	newStone->btn->addTouchEventListener(CC_CALLBACK_2(UpgradeStone::onClick, newStone));
	newStone->type = (UPGRADE_TYPE)cocos2d::RandomHelper::random_int(0, UPGRADE_TYPE::UT_COUNT - 1);
	switch (newStone->type)
	{
	case UPGRADE_TYPE::UT_DAMAGE:
		newStone->modififyingValue = cocos2d::random(0.f, 1.f) * ((float)modifier / 5);
		break;
	case UPGRADE_TYPE::UT_FIRERATE:
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
