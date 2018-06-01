#include "Projectile.h"

#include "HelloWorldScene.h"
#include "Functions.h"

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
	proj->SetPhysics(true, dir * speed, false);

	return proj;
}

//Legit no point for this because when there is alot proj, this will be called alot of times
//doing the same thing. if starting to lag then start migrating
bool Projectile::OnContactBegin(cocos2d::PhysicsContact & contact)
{

	PhysicsShape* shapeA = contact.getShapeA();
	PhysicsShape* shapeB = contact.getShapeB();

	void* userDataA = shapeA->getBody()->getNode()->getUserData();
	void* userDataB = shapeB->getBody()->getNode()->getUserData();

	//Normally proj should be equal this
	//unless you want special effect on projectile collide projectile
	Projectile* proj = GetData<Projectile*>(userDataA, userDataB);
	
	if (!proj)
		return false;

	if (proj->isDead())
		return false;


	proj->Destroy();
	return true;
}
