#include "Weapon.h"

#include "Projectile.h"

Weapon::Weapon()
{
	this->min_damage = 1;
	this->max_damage = 2;

	this->bulletType = 0;
	this->bulletSpeed = 10;
	this->factionTag = -1;

	fast = buff = false;

	fastTimer = 0.0f;
	buffTimer = 0.0f;

	defaultMinDmg = this->min_damage;
	defaultMaxDmg = this->max_damage;

	attackspeed_timer = 0.0f;
	attackspeed_triggerTime = 1.0f;

	isSet = false;
}

Weapon::~Weapon()
{
}

void Weapon::Update(double dt)
{
	attackspeed_timer += dt;
}

int Weapon::GetDamage()
{
	return this->min_damage + (rand() % (this->max_damage - this->min_damage));
}

void Weapon::Discharge()
{
	if (!(attackspeed_timer >= attackspeed_triggerTime))
		return;

	Projectile* proj = Projectile::Create(position, direction, this->GetDamage(), this->bulletSpeed, 1000, this->factionTag);

	proj->SetSprite(bulletTexture, "bullet");
	proj->SetPhysics(true, proj->direction * proj->speed, false);
	proj->physicsBody->setMass(0.1f);
	proj->sprite->setPosition(proj->position);
	proj->sprite->setRotation(-90 + atan2(proj->direction.x, proj->direction.y) * 180 / 3.14159265f);
	if (factionTag == 0)
	{
		proj->physicsBody->setCategoryBitmask(BITMASK_ENUM::BITMASK_PLAYER_BULLET);
		proj->physicsBody->setContactTestBitmask(BITMASK_ENUM::BITMASK_ENEMY);
		proj->physicsBody->setCollisionBitmask(BITMASK_ENUM::BITMASK_ENEMY);
	}
	else {
		proj->physicsBody->setCategoryBitmask(BITMASK_ENUM::BITMASK_ENEMY_BULLET);
		proj->physicsBody->setContactTestBitmask(BITMASK_ENUM::BITMASK_PLAYER);
		proj->physicsBody->setCollisionBitmask(BITMASK_ENUM::BITMASK_PLAYER);
	}

	proj->physicsBody->setTag(proj->id);

	//AudioPlayer::GetInstance()->PlaySound2D("PewPew", 0.2);
	//must reset timer
	attackspeed_timer = 0.0;
}

void Weapon::Set(int min_dmg, int max_dmg, double attacks_per_sec, int bulletType, float bulletSpeed, int factionSide, std::string bulletsprite)
{
	defaultMinDmg = min_dmg;
	defaultMaxDmg = max_dmg;
	this->min_damage = min_dmg;
	this->max_damage = max_dmg;

	this->attackspeed_triggerTime = 1.0 / attacks_per_sec;

	this->bulletType = bulletType;
	this->bulletSpeed = bulletSpeed;
	this->factionTag = factionSide;

	this->isSet = true;

	this->bulletTexture = bulletsprite;
}
