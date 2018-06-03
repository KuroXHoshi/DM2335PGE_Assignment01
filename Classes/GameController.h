#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "cocos2d.h"
#include "SingletonTemplate.h"

using namespace cocos2d;

//singleton to manage the game progression, spawning and background sprites
class GameController : public Singleton<GameController>
{
	friend Singleton<GameController>;
public:
	void Init(Sprite* _player);
	void Update(double dt);

	//gets the array of background sprites
	inline Sprite** GetBackgroundSprites() { return backgrounds; }

private:
	Sprite* player;

	//arrangement of sprites is that of a keypad
	//0 - 1 - 2
	//3 - 4 - 5
	//6 - 7 - 8
	Sprite* backgrounds[9];
	//value from 0 - 1
	float offsetPercent;
	float offsetX;
	float offsetY;
	int gridX;
	int gridY;
	float backgroundWidth;
};

#endif