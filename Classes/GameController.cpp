#include "GameController.h"
#include "Enemy.h"
#include "BossController.h"

//requires a reference to the player
void GameController::Init(Player* _player)
{
	player = _player;

	currState = GS_WAVE;
	prevState = GS_TRANSITION;
	sequences = 0;
	waveCount = 0;
	spawnRate = 2.f;
	spawnTimer = 0.f;
	spawn = true;
	distance = 500.f;
	transitionTime = 1.f;
	transitionTimer = 0.f;
	waveMax = 5;

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

	BossController::GetInstance()->AttachPlayer(player);
}

void GameController::Update(double dt)
{
	//updating the background to follow the player
	if (player->sprite != nullptr)
	{
		gridX = player->sprite->getPosition().x / backgroundWidth;
		gridY = player->sprite->getPosition().y / backgroundWidth;
		for (int j = 0; j < 3; ++j)
		{
			for (int i = 0; i < 3; ++i)
			{
				int index = j * 3 + i;
				backgrounds[index]->setPosition((i - 1 + gridX) * backgroundWidth, (j - 1 + gridY) * backgroundWidth);
			}
		}
	}

	//updating of the game states
	switch (currState)
	{
	case GS_WAVE:
		WaveUpdate(dt);
		break;
	case GS_BOSS:
		BossUpdate(dt);
		break;
	case GS_TRANSITION:
		transitionTimer += dt;
		if (transitionTimer > transitionTime)
		{
			transitionTimer = 0;
			switch (prevState)
			{
			case GS_WAVE:
				currState = GS_BOSS;
				break;
			case GS_BOSS:
				currState = GS_WAVE;
				break;
			}
			prevState = currState;
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

void GameController::WaveUpdate(double dt)
{
	if (spawn)
	{
		//spawning of the enemy
		GenerateWave(dt);
	}
	else
	{
		if (enemyCount == 0)
		{
			this->switchStates();
			spawn = true;
		}
	}
	//if (enemyCount == 0)
	//	spawn = true;
}

void GameController::BossUpdate(double dt)
{
	BossController::GetInstance()->Update(dt);
}

Vec2 GameController::GenerateSpawnPosition()
{
	Vec2 dir;
	dir.x = RandomHelper::random_real(-1.f, 1.f);
	dir.y = RandomHelper::random_real(-1.f, 1.f);
	dir.normalize();
	return player->sprite->getPosition() + dir * distance;
}

void GameController::GenerateWave(double dt)
{
	static int enemySpawnedCount = 0;
	static int enemyMaxSpawn = 5;
	if (enemySpawnedCount <= enemyMaxSpawn)
	{
		spawnTimer += dt;
		if (spawnTimer > spawnRate)
		{
			Enemy* e = Enemy::Create(GenerateSpawnPosition(), player, 50, 5, 75, 2);
			e->SetSprite("textures/Enemy_Oce_Side.tga", "enemy");
			e->SetPhysics(true, Vec2::ZERO, false);

			e->physicsBody->setMass(1);
			e->physicsBody->setCategoryBitmask(BITMASK_ENUM::BITMASK_ENEMY);
			e->physicsBody->setContactTestBitmask(BITMASK_ENUM::BITMASK_PLAYER + BITMASK_PLAYER_BULLET+ BITMASK_ENEMY);
			e->physicsBody->setCollisionBitmask(BITMASK_ENUM::BITMASK_PLAYER + BITMASK_PLAYER_BULLET + BITMASK_ENEMY);
			e->sprite->setPosition(e->position);
			e->sprite->setScale(0.5f);
			e->healthLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 24);
			scene->addChild(e->healthLabel, 1);
			++enemyCount;
			++enemySpawnedCount;
			spawnTimer = 0;
		}
	}
	else 
	{
		spawn = false;
		enemySpawnedCount = 0;
		++enemyMaxSpawn;
	}
}

void GameController::AddScoreOnEnemyKilled()
{
	//need to know what enemy player killed to add score, for now value is fixed
	int enemyScore = 100;
	score += enemyScore * scoreMultiplier;
	//decrease the enemy count
	enemyScore -= 1;
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
