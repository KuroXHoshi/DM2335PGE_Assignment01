#include "GameController.h"

//requires a reference to the player
void GameController::Init(Sprite* _player)
{
	player = _player;
	//setting default values;
	offsetPercent = 0.1;
	offsetX = offsetY = gridX = gridY = 0;
	//loading the textures
	backgroundWidth = Sprite::create("textures/bg_sky2.tga")->getContentSize().width;
	for (int j = 0; j < 3; ++j)
	{
		for (int i = 0; i < 3; ++i)
		{
			int index = j * 3 + i;
			backgrounds[index] = Sprite::create("textures/bg_sky2.tga");
			backgrounds[index]->setPosition((i - 1) * backgroundWidth, (j - 1) * backgroundWidth);
		}
	}
}

void GameController::Update(double dt)
{
	//updating the background to follow the player
	gridX = player->getPosition().x / backgroundWidth;
	gridY = player->getPosition().y / backgroundWidth;
	for (int j = 0; j < 3; ++j)
	{
		for (int i = 0; i < 3; ++i)
		{
			int index = j * 3 + i;
			backgrounds[index]->setPosition((i - 1 + gridX) * backgroundWidth, (j - 1 + gridY) * backgroundWidth);
		}
	}
}