#include "InventoryManager.h"

#include "cocos2d.h"
#include "Player.h"

using namespace cocos2d;

InventoryManager* InventoryManager::s_instance = nullptr;

void InventoryManager::AddStone(UpgradeStone * stone)
{
	//if the number of stones is divisible by stone row count
	//need to create a new horizontal layer
	if (stones.size() % stoneRowCount == 0)
	{
		Layout* horizontalLayout = Layout::create();
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
	stones.push_back(stone);
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
	}
	stoneTypeText->setText(type);
	stoneTypeText->setVisible(true);

	std::string text = "Effect: +";
	text += std::to_string(stone->modififyingValue) + "x";
	stoneValueText->setText(text);
	printf("%s", text.c_str());
	stoneValueText->setVisible(true);
}

void InventoryManager::onStoneStatClose(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		statDisplay->setVisible(false);
		statDisplay->setEnabled(false);
		stoneTypeText->setVisible(false);
		stoneValueText->setVisible(false);
	}
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

	for (int j = 0; j < 10; ++j)
	{
		for (int i = 0; i < 7; ++i)
		{
			UpgradeStone* stone = UpgradeStone::GenerateStone(1, stoneSize);
			AddStone(stone);
		}
	}
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
