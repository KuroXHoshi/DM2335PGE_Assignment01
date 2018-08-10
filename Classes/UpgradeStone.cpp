#include "UpgradeStone.h"

UpgradeStone * UpgradeStone::GenerateStone(int modifier, cocos2d::Size size)
{
	UpgradeStone* newStone = (UpgradeStone*)Button::create("Blue_Front1.png");
	newStone->setSize(size);
	newStone->setAnchorPoint(cocos2d::Vec2(0, 0));
	return newStone;
}
