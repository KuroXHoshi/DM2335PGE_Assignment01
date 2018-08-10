#ifndef UPGRADE_STONE_H
#define UPGRADE_STONE_H

#include "ui\UIButton.h"

using namespace cocos2d::ui;

class UpgradeStone
{
public:
	enum UPGRADE_TYPE
	{
		UT_FIRERATE = 0,
		UT_DAMAGE,
		UT_RANGE,
		UT_CRITCHANCE,
		UT_CRITDAMAGE,
		UT_COUNT
	};

	Button* btn;

	static UpgradeStone* GenerateStone(int modifier, cocos2d::Size size);

	void onClick(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	
	float modififyingValue = 0;
	float baseValue = 0;
	UPGRADE_TYPE type;
	
private:
	UpgradeStone() {};
};

#endif