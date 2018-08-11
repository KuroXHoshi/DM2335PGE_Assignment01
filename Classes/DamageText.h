#ifndef DAMAGE_TEXT_H
#define DAMAGE_TEXT_H

#include "GameObject.h"

class DamageText : public GameObject
{
public:
	Label* textLabel;
	float et = 0.0f;
	float duration = 1.0f;
	float speed = 50.0f;
	int damage = 0;
	bool isCrit = false;

	virtual void Start();
	virtual void Update(double dt);
	virtual void Destroy();

	static DamageText* Create(Vec2& pos, int damage, bool isCrit);
};

#endif
