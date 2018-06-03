#pragma once

#include "GameObject.h"

class Enemy : public GameObject
{
	cocos2d::Vec2 LastPlayerPosition;
	TAGENUM factionTag;
	int health;
	int damage;
	float speed;

	Enemy();
	~Enemy();

public:
	virtual void Start();
	virtual void Update(double dt);

	static Enemy* Create(cocos2d::Vec2 pos, cocos2d::Vec2 playerPos, int damage, float speed, int factionTag);
};