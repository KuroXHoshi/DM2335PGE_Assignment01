#include "GravityBullet.h"

#include "GameController.h"
#include "BossController.h"
#include "MyMath.h"
#include "Vortex.h"

void GravityBullet::Start()
{
	this->physicsBody->setVelocity(Vec2(0, 0));

}

void GravityBullet::Update(double dt)
{
	distTravelled += speed * dt;
	if (distTravelled > range)
		this->Destroy();

	//DBOUT("SPRITE SIZE " << sprite->getBoundingBox().size.width);
	//DBOUT("STATE " << state);

	switch (state)
	{
	case 0:
		FlyStraight(dt);
		break;
	case 1:
		GoThereExplode(dt);
		break;
	}

}

void GravityBullet::Destroy()
{
	GameObject::Destroy();

	//Create the vortex
	Vortex* ss = new Vortex();
	ss->position = this->position;
	ss->direction = this->direction;
	ss->damage = damage;
	ss->speed = this->speed;
	ss->range = this->explosionRange;
	ss->factionTag = this->factionTag;


	ss->isCrit = this->isCrit;
	std::string bulletTexture = this->vortexTexture;
	ss->SetSpriteStuffs(bulletTexture);
}

void GravityBullet::FlyStraight(double dt)
{
	physicsBody->setVelocity(this->direction * speed);
	this->position = sprite->getPosition();
	//this->position += this->direction * speed * dt;

	//this->sprite->setPosition(this->position);

	if (this->factionTag == 0)
	{
		//from player
		int size = GameController::GetInstance()->activeEnemies.size();
		//DBOUT("SIZE " << size);
		GameObject* nearestEnemy = nullptr;
		float shortestRangeSq = std::numeric_limits<float>::max();
		if (size > 0)
		{
			for (int i = 0; i < size; ++i)
			{
				if (!GameController::GetInstance()->activeEnemies[i]->isDead())
				{
					float distSq = (GameController::GetInstance()->activeEnemies[i]->position - this->position).lengthSquared();
					if (distSq > this->detectRange * this->detectRange)
						break;
					nearestEnemy = GameController::GetInstance()->activeEnemies[i];
					shortestRangeSq = distSq;
					break;
				}
			}
		}

		//Check boss distance
		//DBOUT("HASSTARTED " << BossController::GetInstance()->hasStarted);
		if (BossController::GetInstance()->hasStarted == true)
		{
			float bossDistSq = (BossController::GetInstance()->boss->position - this->position).lengthSquared();
			float spriteRadius = BossController::GetInstance()->boss->sprite->getBoundingBox().size.width * 0.5f;
			bossDistSq = bossDistSq - (spriteRadius * spriteRadius);
			if (bossDistSq < this->detectRange * this->detectRange)
			{
				if (bossDistSq < shortestRangeSq)
				{
					nearestEnemy = BossController::GetInstance()->boss;
					shortestRangeSq = bossDistSq;
				}
			}
		}


		if (nearestEnemy != nullptr)
		{
			target = nearestEnemy->position;
			this->state = 1;
		}

	}
	else
	{
		float distSq = (GameController::GetInstance()->player->position - this->position).lengthSquared();
		if (distSq < this->detectRange * this->detectRange)
		{
			target = GameController::GetInstance()->player->position;
			this->state = 1;
		}

	}
}

void GravityBullet::GoThereExplode(double dt)
{
	this->position = sprite->getPosition();
	Vec2 direct = (target - this->position);
	direct.normalize();
	float anglebtw = Vec2::angle(this->direction, direct);

	float norm = this->direction.cross(direct);

	//DBOUT("NORM " << norm << "  ANGLEBTW " << anglebtw);


	float turnAngleInRad = turnAngleSpd / 180.0f * PI;

	float turn = MYMIN(anglebtw, turnAngleInRad * (float)dt);

	if (norm < 0)
		turn = -turn;

	this->direction = this->direction.rotateByAngle(Vec2(0, 0), turn);
	//this->direction = direct;

	if (direct.isZero())
	{
		//explode
		this->Destroy();
		return;
	}

	physicsBody->setVelocity(this->direction * speed);
	//this->position = sprite->getPosition();

	//this->sprite->setPosition(this->position);
}
