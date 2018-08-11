#ifndef VORTEX_H
#define VORTEX_H

#include "Projectile.h"

class Vortex : public Projectile
{
public:
	float et = 0.0f;
	float duration = 3.0f;

	//struct HITINFO
	//{
	//	float ignoreElaspedTime = 0.0f;
	//	GameObject* target;
	//	HITINFO(GameObject* go) { target = go; }
	//};
	//std::vector<HITINFO> hitedGuys;

	virtual void Start();
	virtual void Update(double dt);

	virtual void Destroy();

	//void SetDamage(int damage);

	//bool RegisterHit(GameObject* go);
	//void ClearEnemy(GameObject* go);

	void ApplyGravity(GameObject* go, double dt);
};

#endif