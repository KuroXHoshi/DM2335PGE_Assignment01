#pragma once

#include "GameObject.h"

#include "Weapon.h"
#include "player.h"

class Enemy : public GameObject
{
public:
	//cocos2d::Size VisibleSize;
	Player* player;
	TAGENUM factionTag;
	int health;
	int damage;
	float speed;
	Weapon weap;

	Enemy();
	//~Enemy();

public:
	virtual void Start();
	virtual void Update(double dt);

	static Enemy* Create(cocos2d::Vec2 pos, Player* player, int health, int damage, float speed, int factionTag);

	//bool OnContactBegin(cocos2d::PhysicsContact& contact);
};