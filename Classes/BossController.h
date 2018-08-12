#pragma once

#include "SingletonTemplate.h"
#include "Enemy.h"
#include "Player.h"

class BossController : public Singleton<BossController>
{
	friend Singleton<BossController>;

public:
	Enemy* boss;
	Player* player;

	bool hasStarted = false;
	float stopAtDistance = 250;

	int currState = 0;
	float currStateET = 0.0f;
	float stateChangeTime = 5.0f;

	BossController();
public:
	~BossController();
	
	void AttachPlayer(Player* player) { this->player = player; };
	//Call this before start of a boss game state
	void Start();
	void Update(double dt);
	void End();
};