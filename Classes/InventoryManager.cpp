#include "InventoryManager.h"

#include "cocos2d.h"

using namespace cocos2d;

InventoryManager* InventoryManager::s_instance = nullptr;

void InventoryManager::AddStone(UpgradeStone * stone)
{
	//if the number of stones is divisible by 3
	if (stones.size() % 3 == 0)
	{

	}
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
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	inventoryEnable = Button::create("ZigzagGrass_Mud_Round.png", "ZigzagForest_Square.png");
	inventoryEnable->setPosition(Vec2(visibleSize.width - inventoryEnable->getSize().width, visibleSize.height / 4 * 3 + origin.y));
	inventoryEnable->addTouchEventListener(CC_CALLBACK_2(InventoryManager::onInventoryEnable, this));
	layer->addChild(inventoryEnable);
	inventoryDisable = Button::create("ZigzagForest_Square.png", "ZigzagGrass_Mud_Round.png");
	inventoryDisable->setPosition(Vec2(visibleSize.width - inventoryDisable->getSize().width, visibleSize.height / 4 * 3 + origin.y));
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

	for (int j = 0; j < 10; ++j)
	{
		Layout* test = Layout::create();
		test->setLayoutType(Layout::Type::HORIZONTAL);
		for (int i = 0; i < 5; ++i)
		{
			UpgradeStone* stone = UpgradeStone::GenerateStone(1, Size(50, 50));
			test->addChild(stone);
		}
		test->setPosition(Vec2(0, 50 * j));
		inventoryScrollView->addChild(test);
	}
}

void InventoryManager::Update(float dt)
{
	if (displayInventory && change)
	{
		inventoryScrollView->setEnabled(true);
		inventoryScrollView->setVisible(true);
		inventoryDisable->setEnabled(true);
		inventoryDisable->setVisible(true);
		inventoryEnable->setEnabled(false);
		inventoryEnable->setVisible(false);
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
		change = false;
	}
}
