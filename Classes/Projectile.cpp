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
}

Projectile * Projectile::Create(int damage, float speed, int range, int factionTag)
{
	Projectile* proj = new Projectile();
	proj->damage = damage;
	proj->speed = speed;
	proj->range = range;
	proj->factionTag = factionTag;

	proj->SetSprite("Blue_Front1.png", "proj");

	return proj;
}