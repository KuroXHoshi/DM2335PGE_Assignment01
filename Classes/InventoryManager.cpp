#include "InventoryManager.h"

#include "cocos2d.h"
#include "Player.h"

using namespace cocos2d;

InventoryManager* InventoryManager::s_instance = nullptr;

void InventoryManager::AddStone(UpgradeStone * stone)
{
	//if the number of stones is divisible by stone row count
	//need to create a new horizontal layer
	if (GetStoneCount() % stoneRowCount == 0)
	{
		Layout* horizontalLayout = Layout::create();
		horizontalLayout->retain();
		horizontalLayout->setLayoutType(Layout::Type::HORIZONTAL);
		horizontalLayouts.push_back(horizontalLayout);
		//set the horizontal layout to correct location
		horizontalLayout->setPosition(Vec2(0, stoneSize.height * (horizontalLayouts.size())));
		inventoryScrollView->addChild(horizontalLayout);
		//update container size
		inventoryScrollView->setInnerContainerSize(Size(visibleSize.width, horizontalLayouts.size() * stoneSize.height));
	}
	//get the last layer to add the stone in
	int finalIndex = horizontalLayouts.size() - 1;
	stone->btn->setAnchorPoint(Vec2::ZERO);
	horizontalLayouts[finalIndex]->addChild(stone->btn);
	//add it to respective catergory
	stoneTypes[stone->type].push_back(stone);
	stone->btn->addTouchEventListener(CC_CALLBACK_2(UpgradeStone::onClick, stone));
}

bool sortGreater(UpgradeStone* a, UpgradeStone* b) { return a->modififyingValue > b->modififyingValue; }
bool sortLower(UpgradeStone* a, UpgradeStone* b) { return a->modififyingValue < b->modififyingValue; }

void InventoryManager::SortStone(bool highest)
{
	//using std::sort
	//if sort by highest to lowest
	/*for (auto it : stoneTypes)
	{
		quickSort(it, 0, it.size() - 1);
	}*/
	if (highest)
	{
		//for every type of stones
		for (int i = 0; i < stoneTypes.size(); ++i)
		{
			std::sort(stoneTypes[i].begin(), stoneTypes[i].end(), sortGreater);
		}
	}
	else
	{
		//for every type of stones
		for (int i = 0; i < stoneTypes.size(); ++i)
		{
			std::sort(stoneTypes[i].begin(), stoneTypes[i].end(), sortLower);
		}
	}
	UpdateStonesPositions();
}

void InventoryManager::UpdateStonesPositions()
{
	//remove all the stones from all the layouts
	for (auto it : horizontalLayouts)
	{
		it->removeAllChildrenWithCleanup(false);
	}
	int stoneIndexCount = 0;
	int layoutCount = 0;
	for (int i = stoneTypeSort; i < UpgradeStone::UT_COUNT; ++i)
	{
		for (int j = 0; j < stoneTypes[i].size(); ++j)
		{
			if (stoneIndexCount % stoneRowCount == 0)
				++layoutCount;
			//horizontalLayouts[horizontalLayouts.size() - layoutCount]->addChild(stoneTypes[i][j]->btn);
			horizontalLayouts[horizontalLayouts.size() - layoutCount]->addChild(stoneTypes[i][j]->btn);
			++stoneIndexCount;
		}
	}
	for (int i = 0; i < stoneTypeSort; ++i)
	{
		for (int j = 0; j < stoneTypes[i].size(); ++j)
		{
			if (stoneIndexCount % stoneRowCount == 0)
				++layoutCount;
			//horizontalLayouts[horizontalLayouts.size() - layoutCount]->addChild(stoneTypes[i][j]->btn);
			horizontalLayouts[horizontalLayouts.size() - layoutCount]->addChild(stoneTypes[i][j]->btn);
			++stoneIndexCount;
		}
	}
}

void InventoryManager::AttachPlayer(Player * _player)
{
	player = _player;
	hudLayer->runAction(Follow::create(player->sprite));
}

void InventoryManager::onInventoryEnable(Ref * sender, ui::Widget::TouchEventType type)
{
	displayInventory = true;
	change = true;
}

void InventoryManager::onInventoryDisable(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	displayInventory = false;
	change = true;
}

void InventoryManager::DisplayStoneStat(UpgradeStone * stone)
{
	selectedStone = stone;
	statDisplay->setVisible(true);
	statDisplay->setEnabled(true);

	std::string type = "Type: ";
	switch (stone->type)
	{
	case UpgradeStone::UPGRADE_TYPE::UT_DAMAGE:
		type += "Damage";
		break;
	case UpgradeStone::UPGRADE_TYPE::UT_FIRERATE:
		type += "Firerate";
		break;
	case UpgradeStone::UPGRADE_TYPE::UT_RANGE:
		type += "Range";
		break;
	case UpgradeStone::UPGRADE_TYPE::UT_CRITCHANCE:
		type += "Critical Chance";
		break;
	case UpgradeStone::UPGRADE_TYPE::UT_CRITDAMAGE:
		type += "Critical Damage";
		break;
	}
	stoneTypeText->setText(type);
	stoneTypeText->setVisible(true);

	std::string text = "Effect: +";
	text += std::to_string(stone->modififyingValue) + "x";
	stoneValueText->setText(text);
	printf("%s", text.c_str());
	stoneValueText->setVisible(true);

	for (int i = 0; i < 6; ++i)
	{
		equipButtons[i]->setVisible(true);
		equipButtons[i]->setEnabled(true);
	}
}

void InventoryManager::onStoneStatClose(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		statDisplay->setVisible(false);
		statDisplay->setEnabled(false);
		stoneTypeText->setVisible(false);
		stoneValueText->setVisible(false);
		selectedStone = nullptr;
	}
	for (int i = 0; i < 6; ++i)
	{
		equipButtons[i]->setVisible(false);
		equipButtons[i]->setEnabled(false);
	}
}

void InventoryManager::equipStone(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		for (int i = 0; i < 6; ++i)
		{
			if ((cocos2d::ui::Button*)sender == equipButtons[i])
			{
				if(player->stoneModifiers[i] != nullptr)
					player->stoneModifiers[i]->btn->removeChild(borders[i]);
				player->stoneModifiers[i] = selectedStone;
				hudLayer->removeChild(borders[i]);
				borders[i]->setPosition(Vec2::ZERO);
				selectedStone->btn->addChild(borders[i], 100);
				onStoneStatClose(nullptr, ui::Widget::TouchEventType::ENDED);
			}
		}
	}
}

void InventoryManager::onSort(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		highestOrLowest = !highestOrLowest;
		SortStone(highestOrLowest);
		if (highestOrLowest)
			sortText->setText("Descending");
		else
			sortText->setText("Ascending");
	}
}

void InventoryManager::onSortType(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		++stoneTypeSort;
		if (stoneTypeSort == UpgradeStone::UT_COUNT)
			stoneTypeSort = 0;
		SortStone(highestOrLowest);
		switch (stoneTypeSort)
		{
		case 0:
			sortTypeText->setText("Firerate");
			break;
		case 1:
			sortTypeText->setText("Damage");
			break;
		case 2:
			sortTypeText->setText("Range");
			break;
		case 3:
			sortTypeText->setText("Critical Chance");
			break;
		case 4:
			sortTypeText->setText("Critical Damage");
			break;
		}
	}
}

void InventoryManager::quickSort(std::vector<UpgradeStone*>& stones, int _first_index, int _last_index)
{
	if (_first_index < _last_index) {
		int pivot_location = (int)partition(stones, _first_index, _last_index);
		quickSort(stones, _first_index, pivot_location - 1);
		quickSort(stones, pivot_location + 1, _last_index);
	}
}

int InventoryManager::partition(std::vector<UpgradeStone*>& stones, int _first_index, int _last_index)
{
	int middle_index = (_first_index + _last_index) / 2;
	int pivot_value;
	pivot_value = stones[middle_index]->modififyingValue;
	int small_index = _first_index;

	swap(stones, _first_index, middle_index);

	for (int check_index = (_first_index + 1); check_index <= _last_index; check_index++) {
		int compared_data;
		compared_data = stones[middle_index]->modififyingValue;

		if (compared_data < pivot_value) {
			small_index++;
			swap(stones, small_index, check_index);
		}
	}
	swap(stones, _first_index, small_index);

	return small_index;
}

void InventoryManager::swap(std::vector<UpgradeStone*>& stones, int _first_index, int _second_index)
{
	UpgradeStone* temp = stones[_first_index];
	stones[_first_index] = stones[_second_index];
	stones[_second_index] = temp;
}

InventoryManager::InventoryManager()
{

}

InventoryManager * InventoryManager::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new InventoryManager();
	}
	return s_instance;
}

void InventoryManager::Init(cocos2d::Layer* layer)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	this->hudLayer = layer;

	for (int i = 0; i < UpgradeStone::UPGRADE_TYPE::UT_COUNT; ++i)
	{
		stoneTypes.push_back(std::vector<UpgradeStone*>());
	}
	stoneTypeSort = 0;
	highestOrLowest = true;

	inventoryEnable = Button::create("ZigzagGrass_Mud_Round.png", "ZigzagForest_Square.png");
	inventoryEnable->setPosition(Vec2(visibleSize.width - inventoryEnable->getContentSize().width, visibleSize.height / 4 * 3 + origin.y));
	inventoryEnable->addTouchEventListener(CC_CALLBACK_2(InventoryManager::onInventoryEnable, this));
	layer->addChild(inventoryEnable);
	inventoryDisable = Button::create("ZigzagForest_Square.png", "ZigzagGrass_Mud_Round.png");
	inventoryDisable->setPosition(Vec2(visibleSize.width - inventoryDisable->getContentSize().width, visibleSize.height / 4 * 3 + origin.y));
	inventoryDisable->setEnabled(false);
	inventoryDisable->setVisible(false);
	inventoryDisable->addTouchEventListener(CC_CALLBACK_2(InventoryManager::onInventoryDisable, this));
	layer->addChild(inventoryDisable);

	inventoryScrollView = ScrollView::create();
	inventoryScrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
	inventoryScrollView->setBounceEnabled(true);
	inventoryScrollView->setContentSize(Size(visibleSize.width / 2, visibleSize.height / 2));
	containerSize = Size(visibleSize.width / 2, visibleSize.height / 2);
	inventoryScrollView->setInnerContainerSize(containerSize);
	inventoryScrollView->setPosition(Vec2(visibleSize.width / 5 + origin.x, visibleSize.height / 5 + origin.y));
	inventoryScrollView->setBackGroundImage("textures/background.tga");
	inventoryScrollView->setEnabled(false);
	inventoryScrollView->setVisible(false); 
	layer->addChild(inventoryScrollView);

	stoneRowCount = 7;
	stoneSize.width = containerSize.width / stoneRowCount;
	stoneSize.height = stoneSize.width;

	statDisplay = Button::create("textures/ui_healthbar1.tga");
	statDisplay->setPosition(inventoryScrollView->getPosition() + inventoryScrollView->getContentSize() / 2);
	statDisplay->setScaleX((inventoryScrollView->getContentSize().width / statDisplay->getContentSize().width));
	statDisplay->setScaleY((inventoryScrollView->getContentSize().height / statDisplay->getContentSize().height));
	statDisplay->addTouchEventListener(CC_CALLBACK_2(InventoryManager::onStoneStatClose, this));
	statDisplay->setEnabled(false);
	statDisplay->setVisible(false);
	layer->addChild(statDisplay, 100);

	stoneTypeText = Text::create();
	stoneTypeText->setContentSize(statDisplay->getContentSize() / 2);
	stoneTypeText->setPosition(Vec2(statDisplay->getPosition().x, statDisplay->getContentSize().height / 4 + statDisplay->getPosition().y));
	stoneTypeText->setColor(Color3B::BLACK);
	stoneTypeText->setFontSize(20);
	stoneTypeText->setVisible(false);
	layer->addChild(stoneTypeText, 101);

	stoneValueText = Text::create();
	stoneValueText->setContentSize(statDisplay->getContentSize() / 2);
	stoneValueText->setPosition(Vec2(statDisplay->getPosition().x, statDisplay->getPosition().y - statDisplay->getContentSize().height / 4));
	stoneValueText->setColor(Color3B::BLACK);
	stoneValueText->setFontSize(20);
	stoneValueText->setVisible(false);
	layer->addChild(stoneValueText, 101);

	borders[0] = Sprite::create("textures/dark_red.png");
	borders[1] = Sprite::create("textures/green.png");
	borders[2] = Sprite::create("textures/yellow.png");
	borders[3] = Sprite::create("textures/pink.png");
	borders[4] = Sprite::create("textures/light_blue.png");
	borders[5] = Sprite::create("textures/orange.png");

	equipButtons[0] = Button::create("textures/dark_red.png");
	equipButtons[1] = Button::create("textures/green.png");
	equipButtons[2] = Button::create("textures/yellow.png");
	equipButtons[3] = Button::create("textures/pink.png");
	equipButtons[4] = Button::create("textures/light_blue.png");
	equipButtons[5] = Button::create("textures/orange.png");
	for (int i = 0; i < 6; ++i)
	{
		borders[i]->setPosition(Vec2(-100, 0));
		borders[i]->setScaleX((stoneSize.width / borders[i]->getContentSize().width));
		borders[i]->setScaleY((stoneSize.height / borders[i]->getContentSize().height));
		borders[i]->setAnchorPoint(Vec2::ZERO);
		borders[i]->retain();
		//borders[i]->setVisible(false);
		layer->addChild(borders[i], 102);

		equipButtons[i]->setPosition(Vec2(inventoryScrollView->getPosition().x + i * inventoryScrollView->getContentSize().width / 6, inventoryScrollView->getPosition().y));
		equipButtons[i]->setAnchorPoint(Vec2::ZERO);
		equipButtons[i]->setScaleX((inventoryScrollView->getContentSize().width / 6 / equipButtons[i]->getContentSize().width));
		equipButtons[i]->setScaleY((inventoryScrollView->getContentSize().width / 6 / equipButtons[i]->getContentSize().height));
		equipButtons[i]->addTouchEventListener(CC_CALLBACK_2(InventoryManager::equipStone, this));
		equipButtons[i]->setVisible(false);
		equipButtons[i]->setEnabled(false);
		layer->addChild(equipButtons[i], 102);
	}
	sortButton = Button::create("textures/grey.png"); 
	sortButton->setPosition(Vec2(inventoryScrollView->getPosition().x + inventoryScrollView->getContentSize().width / 4, inventoryScrollView->getPosition().y + inventoryScrollView->getContentSize().height / 6 * 7));
	sortButton->setScaleX((inventoryScrollView->getContentSize().width / 2 / sortButton->getContentSize().width));
	sortButton->setScaleY((inventoryScrollView->getContentSize().height / 6 / sortButton->getContentSize().height));
	sortButton->addTouchEventListener(CC_CALLBACK_2(InventoryManager::onSort, this));
	sortButton->setVisible(false);
	sortButton->setEnabled(false);
	layer->addChild(sortButton, 102);
	sortText = Text::create();
	sortText->setText("Descending");
	sortText->setPosition(sortButton->getPosition());
	sortText->setFontSize(30);
	sortText->setColor(Color3B::WHITE);
	sortText->setVisible(false);
	layer->addChild(sortText, 102);

	sortType = Button::create("textures/grey.png");
	sortType->setPosition(Vec2(inventoryScrollView->getPosition().x + inventoryScrollView->getContentSize().width / 4 * 3, inventoryScrollView->getPosition().y + inventoryScrollView->getContentSize().height /6 * 7));
	sortType->setScaleX((inventoryScrollView->getContentSize().width / 2 / sortType->getContentSize().width));
	sortType->setScaleY((inventoryScrollView->getContentSize().height / 6 / sortType->getContentSize().height));
	sortType->addTouchEventListener(CC_CALLBACK_2(InventoryManager::onSortType, this));
	sortType->setVisible(false);
	sortType->setEnabled(false);
	layer->addChild(sortType, 102);
	sortTypeText = Text::create();
	sortTypeText->setText("Firerate");
	sortTypeText->setPosition(sortType->getPosition());
	sortTypeText->setFontSize(30);
	sortTypeText->setColor(Color3B::WHITE);
	sortTypeText->setVisible(false);
	layer->addChild(sortTypeText, 102);
}

void InventoryManager::Update(float dt)
{
	//layer follow player
	if (player != nullptr)
		hudLayer->setPosition(player->sprite->getPosition() - visibleSize * 0.5f);
	if (displayInventory && change)
	{
		inventoryScrollView->setEnabled(true);
		inventoryScrollView->setVisible(true);
		inventoryDisable->setEnabled(true);
		inventoryDisable->setVisible(true);
		inventoryEnable->setEnabled(false);
		inventoryEnable->setVisible(false);
		sortButton->setEnabled(true);
		sortButton->setVisible(true);
		sortType->setEnabled(true);
		sortType->setVisible(true);
		sortText->setVisible(true);
		sortTypeText->setVisible(true);
		change = false;
	}
	if (!displayInventory && change)
	{
		inventoryScrollView->setEnabled(false);
		inventoryScrollView->setVisible(false);
		inventoryDisable->setEnabled(false);
		inventoryDisable->setVisible(false);
		inventoryEnable->setEnabled(true);
		inventoryEnable->setVisible(true);
		sortButton->setEnabled(false);
		sortButton->setVisible(false);
		sortType->setEnabled(false);
		sortType->setVisible(false);
		sortText->setVisible(false);
		sortTypeText->setVisible(false);
		change = false;
	}
}
