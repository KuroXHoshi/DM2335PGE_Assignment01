#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "cocos2d.h"
#include "SingletonTemplate.h"

#include "Player.h"

using namespace cocos2d;

//game states
enum GAME_STATE
{
	GS_WAVE,
	GS_BOSS,
	GS_TRANSITION
};

//singleton to manage the game progression, spawning and background sprites
class GameController : public Singleton<GameController>
{
	friend Singleton<GameController>;
public:
	void Init(Player* _player);
	void Update(double dt);

	//gets the array of background sprites
	inline Sprite** GetBackgroundSprites() { return backgrounds; }

	//change game state to another state
	void switchStates();

	//wave related functions
	//generate a wave based on difficulty and wave count
	//void GenerateWave();
	//call this function when cleared a wave
	//void ClearWave();

	//boss related functions
	//generate a boss based on how far the player progressed
	//void GenerateBoss();

	//score related functions
	//call this function when player killed an enemy
	void AddScoreOnEnemyKilled();
	//call this function when player hit an enemy
	void AddMultiplierOnEnemyHit();
	//call this function when player killed a boss
	void AddScoreOnBossKilled();
	//call this function when player hit a boss
	void AddScoreOnBossHit();

private:
	Player* player;

	GAME_STATE currState;
	GAME_STATE prevState;

	//value to adjust difficulty of game
	int difficulty;
	//how many sequences the player cleared
	int sequences;
	//number of waves atm
	int waveCount;
	//how many waves there can be
	int waveMax;
	//timer for how long the transition will last
	float transitionTime;
	float transitionTimer;

	//score of the player
	int score;
	//multiplier to score
	float scoreMultiplier;
	//how much to add to the score multiplier for enemy
	float multiplierAdderE;
	//how much to add to the score multiplier for boss
	float multiplierAdderB;
	//decay rate of the score multiplier per second
	float multiplierDecayRate;

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