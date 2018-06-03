#pragma once

#include "SingletonTemplate.h"
#include "Enemy.h"
#include "Player.h"

class BossController : public Singleton<BossController>
{
	friend Singleton<BossController>;

	Enemy* boss;
	Player* player;

	bool hasStarted = false;
	float stopAtDistance = 250;

	BossController();
public:
	~BossController();
	
	void AttachPlayer(Player* player) { this->player = player; };
	//Call this before start of a boss game state
	void Start();
	void Update(double dt);
	void End();
};