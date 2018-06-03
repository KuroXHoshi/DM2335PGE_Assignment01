#include "GameController.h"

//requires a reference to the player
void GameController::Init(Sprite* _player)
{
	player = _player;

	currState = GS_WAVE;
	prevState = GS_TRANSITION;
	sequences = 0;
	waveCount = 0;
	waveMax = 5;
	transitionTime = 1.f;
	transitionTimer = 0.f;

	score = 0;
	scoreMultiplier = 1.f;
	multiplierAdderE = 0.05f;
	multiplierAdderB = 0.02f;
	multiplierDecayRate = 0.5f;

	//background related stuff
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

	//updating of the game states
	switch (currState)
	{
	case GS_WAVE:
		if (waveCount > waveMax)
			switchStates();
		break;
	case GS_BOSS:

		break;
	case GS_TRANSITION:
		transitionTimer += dt;
		if (transitionTimer > transitionTime)
		{
			transitionTimer = 0;
			prevState = currState;
			switch (prevState)
			{
			case GS_WAVE:
				currState = GS_BOSS;
				break;
			case GS_BOSS:
				currState = GS_WAVE;
				break;
			}
		}
		break;
	default:
		break;
	}

	//updating of the score multiplier decay
	if (scoreMultiplier > 0)
	{
		scoreMultiplier -= multiplierDecayRate * dt;
	}
	else
		scoreMultiplier = 0;
}

void GameController::switchStates()
{
	prevState = currState;
	currState = GS_TRANSITION;
}

void GameController::AddScoreOnEnemyKilled()
{
	//need to know what enemy player killed to add score, for now value is fixed
	int enemyScore = 100;
	score += enemyScore * scoreMultiplier;
}

void GameController::AddMultiplierOnEnemyHit()
{
	scoreMultiplier += multiplierAdderE;
}

void GameController::AddScoreOnBossKilled()
{
	//need to know what kind of boss it is to add score, for now fixed
	int bossScore = 1000;
	score += bossScore;
}

void GameController::AddScoreOnBossHit()
{
	//need to know what type of boss it is, preferably damage dealt
	int bossHitScore = 10;
	scoreMultiplier += multiplierAdderB;
	score += bossHitScore * scoreMultiplier;
}
