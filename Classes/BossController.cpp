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
	boss = Enemy::Create(Vec2(0, 0), nullptr, 500, 10, 100, TAGENUM::ENEMY);
	boss->SetSprite("textures/Sheep_idle.tga", "Boss");

	boss->healthLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 24);
	GameController::GetInstance()->scene->addChild(boss->healthLabel, 1);

	Vec2 spawnPos = GameController::GetInstance()->GenerateSpawnPosition();
	boss->sprite->setPosition(spawnPos);
	boss->position = spawnPos;
	boss->health = 200;
	boss->weap.Set(10, 20, 2, 0, 175, 1, "textures/EnemyBullet_01.tga");

	boss->sprite->setScale(0.3f);
	boss->sprite->retain();

	hasStarted = true;
	boss->active = true;
	boss->player = player;
	boss->SetPhysics(true, Vec2(0, 0), false);
	boss->physicsBody->setCategoryBitmask(BITMASK_ENUM::BITMASK_ENEMY);
	boss->physicsBody->setContactTestBitmask(BITMASK_ENUM::BITMASK_PLAYER + BITMASK_ENUM::BITMASK_PLAYER_BULLET);
	boss->physicsBody->setCollisionBitmask(BITMASK_ENUM::BITMASK_PLAYER + BITMASK_ENUM::BITMASK_PLAYER_BULLET);
	
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
		boss->speed = 100.0f;
	}
	else
		//Dont chase
		boss->speed = 0.0f;
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
