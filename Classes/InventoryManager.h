#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include <vector>
#include "UpgradeStone.h"

class InventoryManager
{
public:
	InventoryManager* GetInstance();

	//bool to control rendering of inventory
	bool displayInventory = false;
	std::vector<UpgradeStone*> stones;

private:
	InventoryManager();

	static InventoryManager* s_instance;
};

#endif