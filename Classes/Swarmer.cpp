#include "Swarmer.h"

#include "MyMath.h"
#include "Enemy.h"
#include "Player.h"
#include "GameController.h"
#include "BossController.h"

void Swarmer::Start()
{
	this->physicsBody->setVelocity(Vec2(0, 0));

	this->antiClockwise = (rand() % 2 ? true : false );
	this->SetStartRadian(this->direction);
}

void Swarmer::Update(double dt)
{
	distTravelled += speed * dt;
	if (distTravelled > range)
		this->Destroy();

	if (parent == nullptr)
	{
		this->Destroy();
		return;
	}

	//DBOUT("STATE " << state);

	switch (state)
	{
	case 0:
		MoveToCircumference(dt);
		break;
	case 1:
		RotateAround(dt);
		break;
	case 2:
		ChaseTarget(dt);
		break;
	}

}

void Swarmer::SetStartRadian(Vec2 dir)
{
	//0 rad is at x = 1, y = 0
	initialRad = atan2(dir.y, dir.x);
}

void Swarmer::MoveToCircumference(double dt)
{
	float radiusAroundParent = parent->sprite->getBoundingBox().size.width;
	Vec2 intendedPos(radiusAroundParent * cos(initialRad) + parent->position.x,
		radiusAroundParent * sin(initialRad) + parent->position.y);

	Vec2 myPosToIntended = -this->position + intendedPos;

	float moveSpdAtThisFrame = this->speed * dt;

	if (myPosToIntended.length() > moveSpdAtThisFrame)
	{
		this->position = this->position + myPosToIntended.getNormalized() * moveSpdAtThisFrame;

	}
	else
	{
		this->position = intendedPos;
		state = 1;
	}

	this->sprite->setPosition(this->position);
}

void Swarmer::RotateAround(double dt)
{
	float radiusAroundParent = parent->sprite->getBoundingBox().size.width;
	
	//float distanceFromParent = (this->position - parent->position).length();
	//if (distanceFromParent <)
	float isPositive = antiClockwise ? 1.0f : -1.0f;
	float currRad = isPositive * ((float)distTravelled / (float)range) * (PI * 2.0f) + initialRad;
	Vec2 intendedPos(radiusAroundParent * cos(currRad) + parent->position.x,
		radiusAroundParent * sin(currRad) + parent->position.y);

	this->position = intendedPos;

	this->sprite->setPosition(position);

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
			this->state = 2;
		}
		
	}
	else
	{
		float distSq = (GameController::GetInstance()->player->position - this->position).lengthSquared();
		if (distSq < this->detectRange)
		{
			target = GameController::GetInstance()->player->position;
			this->state = 2;
		}
		
	}
}

void Swarmer::ChaseTarget(double dt)
{
	Vec2 intendedPos(target);

	Vec2 myPosToIntended = -this->position + intendedPos;

	float moveSpdAtThisFrame = this->speed * dt;

	if (myPosToIntended.length()  > moveSpdAtThisFrame)
	{
		this->position = this->position + myPosToIntended.getNormalized() * moveSpdAtThisFrame;

	}
	else
	{
		//explode
		this->position = intendedPos;
		this->Destroy();
	}

	this->sprite->setPosition(this->position);

}
