#include "Weapon.h"


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
	//if (!attackspeed_timer >= attackspeed_triggerTime)
	//	return;

	//DmgHitBox* temp_proj = DmgHitBoxManager::GetInstance()->get_hitbox(proj_type);
	//if (!temp_proj)
	//	return;
	//temp_proj->set(this->pos, this->dir, this->faction.side, power.force, damage.get_damage(), damage.get_type());

	////i let u travel 50units bah
	//temp_proj->set_die_condition(new DieToDistance(100, power.force));
	//temp_proj->active = true;

	//PhysicsManager::GetInstance()->add_object(temp_proj, temp_proj->get_physics_component());
	//CollisionManager::GetInstance()->add_collider(temp_proj->get_collider_component());
	//RenderManager::GetInstance()->attach_renderable(temp_proj, 1);

	////AudioPlayer::GetInstance()->PlaySound2D("PewPew", 0.2);
	////must reset timer
	//attackspeed_timer - 0.0;
}

void Weapon::Set(int min_dmg, int max_dmg, double attacks_per_sec, int bulletType, float bulletSpeed, int factionSide)
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
}
