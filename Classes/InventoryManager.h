#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include <vector>
#include "UpgradeStone.h"
#include "ui\UIScrollView.h"
#include "ui\UILayout.h"

class InventoryManager
{
public:
	static InventoryManager* GetInstance();
	void Init(cocos2d::Layer* layer);
	void Update(float dt);

	//bool to control rendering of inventory
	bool displayInventory = false;
	bool change = false;
	std::vector<UpgradeStone*> stones;

	void onInventoryEnable(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void onInventoryDisable(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

private:
	InventoryManager();
	static InventoryManager* s_instance;

	Button* inventoryEnable;
	Button* inventoryDisable;

	ScrollView* inventoryScrollView;
};

#endif