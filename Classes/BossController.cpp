#include "BossController.h"

#include "GameController.h"

BossController::BossController()
{
	hasStarted = false;
}

BossController::~BossController()
{
}

void BossController::Start()
{
	boss = Enemy::Create(Vec2(0, 0), nullptr, 10, 50, TAGENUM::ENEMY);
	boss->SetSprite("textures/Sheep_idle.tga", "Boss");


	Vec2 spawnPos = GameController::GetInstance()->GenerateSpawnPosition();
	boss->sprite->setPosition(spawnPos);
	boss->position = spawnPos;
	boss->health = 500;
	boss->weap.Set(10, 20, 2, 0, 175, 1);
	boss->sprite->setScale(0.5f);
	hasStarted = true;
	boss->active = true;
	boss->player = player;
	boss->SetPhysics(true, Vec2(0, 0), false);
}

void BossController::Update(double dt)
{
	if (hasStarted == false)
		Start();

	if (boss->health <= 0)
	{
		End();
		return;
	}

	Vec2 me_to_player = player->sprite->getPosition() - boss->sprite->getPosition();
	//me_to_player.normalize();

	//Mvoe towards player
	if (me_to_player.lengthSquared() > stopAtDistance * stopAtDistance)
	{
		boss->speed = 0.0f;
	}
	else
		boss->speed = 50.0f;
	//boss->sprite->setRotation()

	boss->weap.position.set(boss->sprite->getPosition());
	boss->weap.direction.set(me_to_player.getNormalized());
	boss->weap.Discharge();
}

void BossController::End()
{
	hasStarted = false;
	GameController::GetInstance()->switchStates();
	boss->Destroy();
}
