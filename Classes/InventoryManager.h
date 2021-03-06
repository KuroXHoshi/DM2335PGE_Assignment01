#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include <vector>
#include "UpgradeStone.h"
#include "ui\UIScrollView.h"
#include "ui\UILayout.h"
#include "ui\UIButton.h"
#include "ui\UIText.h"

class Player;
class InventoryManager
{
public:
	static InventoryManager* GetInstance();
	void Init(cocos2d::Layer* layer);
	void Update(float dt);

	//bool to control rendering of inventory
	bool displayInventory = false;
	bool change = false;
	int stoneRowCount;
	cocos2d::Size containerSize;
	cocos2d::Size stoneSize;
	std::vector<Layout*> horizontalLayouts;

	cocos2d::ui::Button* statDisplay;
	cocos2d::ui::Text* stoneTypeText;
	cocos2d::ui::Text* stoneValueText;
	UpgradeStone* selectedStone;

	cocos2d::Sprite* borders[6];
	cocos2d::ui::Button* equipButtons[6];

	Player* player;
	cocos2d::Layer* hudLayer;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::ui::Button* sortButton;
	cocos2d::ui::Button* sortType;
	cocos2d::ui::Text* sortText;
	cocos2d::ui::Text* sortTypeText;

	cocos2d::ui::Button* changeWeapon;
	cocos2d::ui::Text* changeWeaponText;
	int weap = 0;

	inline int GetStoneCount() { int i = 0; for (auto it : stoneTypes) i += it.size(); return i; }

	void AttachPlayer(Player*);

	void AddStone(UpgradeStone* stone);
	void SortStone(bool highest);
	void UpdateStonesPositions();

	//callback function
	void onInventoryEnable(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void onInventoryDisable(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void DisplayStoneStat(UpgradeStone* stone);
	void onStoneStatClose(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void equipStone(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void onSort(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void onSortType(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void onChangeWeapon(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	//sorting functions
	void quickSort(std::vector<UpgradeStone*> &stones, int _first_index, int _last_index);
	int partition(std::vector<UpgradeStone*> &stones, int _first_index, int _last_index);
	void swap(std::vector<UpgradeStone*> &stones, int _first_index, int _second_index);
	

private:
	InventoryManager();
	static InventoryManager* s_instance;

	Button* inventoryEnable;
	Button* inventoryDisable;

	std::vector<std::vector<UpgradeStone*>> stoneTypes;
	int stoneTypeSort;
	bool highestOrLowest;

	ScrollView* inventoryScrollView;
};

#endif