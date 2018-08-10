#pragma once

#include "GameObject.h"

class Projectile : public GameObject
{
	
	int distTravelled;
public:
	Projectile();
	int damage;
	float speed;
	int range;
	int factionTag;
	bool isCrit;
	virtual void Update(double dt);
	virtual void Start();

	static Projectile* Create(cocos2d::Vec2 pos, cocos2d::Vec2 dir, int damage, float speed, int range, int factionTag);

	bool OnContactBegin(cocos2d::PhysicsContact & contact);

	void SetSpriteStuffs(std::string texture);
};