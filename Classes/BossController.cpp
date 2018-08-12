#include "BossController.h"

#include "GameController.h"
#include "MyMath.h"
#include "WeaponGenerator.h"

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

	int randWeap = rand() % 3;
	//randWeap = 2;
	switch (randWeap)
	{
	//case 1:
	//	boss->weap.Set(5, 13, 2, 2, 200, 1, "textures/EnemyBullet_01.tga");
	//	break;
	//case 2:
	//	boss->weap.Set(3, 18, 1.5, 5, 300, 1, "textures/EnemyBullet_01.tga");
	//	break;
	default:
		boss->weap.Set(10, 20, 2, 0, 175, 1, "textures/EnemyBullet_01.tga");
		break;
	}
	//weaps[0] = WeaponGenerator::GetInstance()->GetWeapon(WEAPON_TYPES::RIFLE, 1);
	//weaps[0]->bulletSpeed = 175;
	//weaps[1] = WeaponGenerator::GetInstance()->GetWeapon(WEAPON_TYPES::FLAMETHROWER, 1);
	//weaps[1]->bulletSpeed = 200;
	//weaps[2] = WeaponGenerator::GetInstance()->GetWeapon(WEAPON_TYPES::SUCTION_GUN, 1);
	//weaps[2]->bulletSpeed = 175;
	

	boss->sprite->setScale(0.3f);
	boss->sprite->retain();

	hasStarted = true;
	boss->active = true;
	boss->player = player;
	boss->SetPhysics(true, Vec2(0, 0), false);
	boss->physicsBody->setCategoryBitmask(BITMASK_ENUM::BITMASK_ENEMY);
	boss->physicsBody->setContactTestBitmask(BITMASK_ENUM::BITMASK_PLAYER + BITMASK_ENUM::BITMASK_PLAYER_BULLET);
	boss->physicsBody->setCollisionBitmask(BITMASK_ENUM::BITMASK_PLAYER + BITMASK_ENUM::BITMASK_PLAYER_BULLET);
	
	currState = rand() % stateCount;
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

	currStateET += dt;
	if (currStateET > stateChangeTime)
	{
		currStateET = 0.0f;
		int prevState = currState;
		while (currState == prevState)
			currState = rand() % stateCount;
	}


	switch (currState)
	{
	case 1:
		State1(dt);
		break;
	case 2:
		State2(dt);
		break;
	default:
		State0(dt);
		break;
	}


}

void BossController::End()
{
	hasStarted = false;
	GameController::GetInstance()->switchStates();
	boss->Destroy();
}

void BossController::State0(double dt)
{
	Vec2 me_to_player = player->sprite->getPosition() - boss->sprite->getPosition();
	boss->weap.position.set(boss->sprite->getPosition());
	boss->weap.direction.set(me_to_player.getNormalized());
	boss->weap.Discharge();
}

void BossController::State1(double dt)
{
	Vec2 me_to_player = player->sprite->getPosition() - boss->sprite->getPosition();

	if (boss->weap.attackspeed_timer < boss->weap.attackspeed_triggerTime)
		return;

	int numOfTurns = 10;
	float radPerTurn = 2.0f * PI / numOfTurns;
	for (int i = 0; i < numOfTurns; ++i)
	{
		me_to_player = me_to_player.rotateByAngle(Vec2(0, 0), radPerTurn);

		boss->weap.position.set(boss->sprite->getPosition());
		boss->weap.direction.set(me_to_player.getNormalized());

		boss->weap.attackspeed_timer = boss->weap.attackspeed_triggerTime;

		boss->weap.Discharge();
	}

}

void BossController::State2(double dt)
{
	Vec2 me_to_player = player->sprite->getPosition() - boss->sprite->getPosition();

	if (!(currStateET >= 1.0f && currStateET <= 2.0f || currStateET >= 3.0f && currStateET <= 4.0f))
		return;

	if (boss->weap.attackspeed_timer < 0.1f)
		return;

	int numOfTurns = 5;
	float radPerTurn = 2.0f * PI / numOfTurns;
	float turnSpeed = PI / 2.0f; //90deg

	for (int i = 0; i < numOfTurns; ++i)
	{
		me_to_player = me_to_player.rotateByAngle(Vec2(0, 0), radPerTurn + currStateET * turnSpeed);

		boss->weap.position.set(boss->sprite->getPosition());
		boss->weap.direction.set(me_to_player.getNormalized());

		boss->weap.attackspeed_timer = boss->weap.attackspeed_triggerTime;

		boss->weap.Discharge();
	}

}
