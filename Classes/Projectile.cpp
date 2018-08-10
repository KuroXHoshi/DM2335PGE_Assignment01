#include "Projectile.h"

#include "HelloWorldScene.h"
#include "Functions.h"

Projectile::Projectile() : distTravelled(0), damage(0), speed(10.0f), range(100), factionTag(-1)
{

}

void Projectile::Update(double dt)
{
	physicsBody->setVelocity(this->direction * speed);
	this->position += this->direction * speed * dt;
	distTravelled += speed * dt;
	if (distTravelled > range)
		this->Destroy();

	//this->sprite->setPosition(this->position);
}

void Projectile::Start()
{
	//this->SetSprite("Blue_Front1.png", "proj");
	//this->SetPhysics(true, direction * speed, false);
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

void Projectile::SetSpriteStuffs(std::string bulletTexture)
{
	Projectile* proj = this;
	proj->SetSprite(bulletTexture, "bullet");
	proj->SetPhysics(true, proj->direction * proj->speed, false);
	proj->physicsBody->setMass(0.1f);
	proj->sprite->setPosition(proj->position);
	proj->sprite->setRotation(-90 + atan2(proj->direction.x, proj->direction.y) * 180 / 3.14159265f);
	if (proj->factionTag == 0)
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

}
