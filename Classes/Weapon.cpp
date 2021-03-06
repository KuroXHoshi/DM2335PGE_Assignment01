#include "Weapon.h"

#include "Projectile.h"
#include "WeaponGenerator.h"

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

void Weapon::Discharge(CocosDenshion::SimpleAudioEngine *audio)
{
	if (!(attackspeed_timer >= attackspeed_triggerTime))
		return;
	if(audio != nullptr)
	audio->playEffect("sounds/shoot.mp3");
	Projectile* proj = WeaponGenerator::GetInstance()->GetProjectile(this);

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
