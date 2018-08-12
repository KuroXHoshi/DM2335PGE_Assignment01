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
	float stopAtDistance = 300;

	int currState = 0;
	float currStateET = 0.0f;
	float stateChangeTime = 5.0f;
	int stateCount = 3;

	BossController();

	//Weapon* weaps[5];
public:
	~BossController();
	
	void AttachPlayer(Player* player) { this->player = player; };
	//Call this before start of a boss game state
	void Start();
	void Update(double dt);
	void End();

	void State0(double dt);
	void State1(double dt);
	void State2(double dt);
};