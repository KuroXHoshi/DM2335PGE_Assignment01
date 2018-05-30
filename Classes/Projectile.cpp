#include "Projectile.h"

Projectile::Projectile() : distTravelled(0), damage(0), speed(10.0f), range(100), factionTag(-1)
{

}

void Projectile::Update(double dt)
{
	this->position += this->direction * speed * dt;
	distTravelled += speed * dt;
	if (distTravelled > range)
		this->Destroy();

	this->sprite->setPosition(this->position);
}

Projectile * Projectile::Create(cocos2d::Vec2 pos, cocos2d::Vec2 dir, int damage, float speed, int range, int factionTag)
{
	Projectile* proj = new Projectile();
	proj->position = pos;
	proj->direction = dir;
	proj->damage = damage;
	proj->speed = speed;
	proj->range = range;
	proj->factionTag = factionTag;

	proj->SetSprite("Blue_Front1.png", "proj");
	

	return proj;
}