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

	static Projectile* Create(cocos2d::Vec2 pos, cocos2d::Vec2 dir, int damage, float speed, int range, int factionTag);
};