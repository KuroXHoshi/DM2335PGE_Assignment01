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
