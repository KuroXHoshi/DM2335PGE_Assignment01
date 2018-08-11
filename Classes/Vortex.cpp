#include "Vortex.h"

#include "GameController.h"
#include "BossController.h"

void Vortex::Start()
{
	this->physicsBody->setVelocity(Vec2(0, 0));
	this->sprite->setPosition(this->position);

	Size contentSize = this->sprite->getContentSize();
	float scaleX = range * 0.25f / contentSize.width;
	float scaleY = range * 0.25f / contentSize.height;
	this->sprite->setScale(scaleX, scaleY);
	this->physicsBody->setMass(PHYSICS_INFINITY);
	this->physicsBody->setRotationEnable(false);

	//this->physicsBody->setEnabled(false);
}

void Vortex::Update(double dt)
{
	//float tickTime = 1.0f / ticksPerSec;
	//for (std::vector<HITINFO>::iterator it = hitedGuys.begin(); it != hitedGuys.end(); )
	//{
	//	(*it).ignoreElaspedTime += dt;

	//	if ((*it).ignoreElaspedTime > tickTime)
	//	{
	//		it = hitedGuys.erase(it);
	//		continue;
	//	}
	//	if ((*it).target == nullptr)
	//	{
	//		it = hitedGuys.erase(it);
	//		continue;
	//	}
	//	++it;
	//}

	this->et += dt;
	if (et >= duration)
	{
		this->isDone = true;
		return;
	}


	if (this->factionTag == 0)
	{
		//from player
		int size = GameController::GetInstance()->activeEnemies.size();

		if (size > 0)
		{
			for (int i = 0; i < size; ++i)
			{
				if (!GameController::GetInstance()->activeEnemies[i]->isDead())
				{
					float distSq = (GameController::GetInstance()->activeEnemies[i]->position - this->position).lengthSquared();
					if (distSq > this->range * this->range)
						break;

					this->ApplyGravity(GameController::GetInstance()->activeEnemies[i], dt);
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
			if (bossDistSq < this->range * this->range)
			{
				this->ApplyGravity(BossController::GetInstance()->boss ,dt);
			}
		}

	}
	else
	{
		float distSq = (GameController::GetInstance()->player->position - this->position).lengthSquared();
		if (distSq < this->range * this->range)
		{
			this->ApplyGravity(GameController::GetInstance()->player, dt);
		}

	}
}

void Vortex::Destroy()
{
	//this->active = false;
}

//void Vortex::SetDamage(int damage)
//{
//	//int totalTicks = duration / (1.0f / ticksPerSec);
//
//	//this->damage = damage / totalTicks;
//
//	//DBOUT("DAMAGE " << this->damage << "  DMG " << damage);
//}

//bool Vortex::RegisterHit(GameObject * go)
//{
//	for (std::vector<HITINFO>::iterator it = hitedGuys.begin(); it != hitedGuys.end(); ++it)
//	{
//		if ((*it).target == go)
//		{
//			return false;
//		}
//	}
//
//	hitedGuys.push_back(HITINFO(go));
//	return true;
//}
//
//void Vortex::ClearEnemy(GameObject * go)
//{
//	for (std::vector<HITINFO>::iterator it = hitedGuys.begin(); it != hitedGuys.end(); ++it)
//	{
//		if ((*it).target == go)
//		{
//			it = hitedGuys.erase(it);
//			break;
//		}
//	}
//}

void Vortex::ApplyGravity(GameObject * go, double dt)
{
	Vec2 meToVor = -go->position + this->position;
	meToVor.normalize();
	//go->physicsBody->applyForce(meToVor * 1000.0f);

	//DBOUT("WAD");
	//force set the position
	Vec2 goPos = go->sprite->getPosition();
	goPos += meToVor * 200.0f * dt;
	go->sprite->setPosition(goPos);
	go->position = goPos;

}
