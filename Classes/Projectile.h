#pragma once

#include "GameObject.h"

class Projectile : public GameObject
{
	Projectile();
	int distTravelled;
public:
	int damage;
	float speed;
	int range;
	int factionTag;

	virtual void Update(double dt);

	static Projectile* Create(int damage, float speed, int range, int factionTag);
};