#ifndef FLAME_H
#define FLAME_H

#include "Projectile.h"

class Flame : public Projectile
{
public:
	float inaccuracyDegCone = 20.0f;

	virtual void Start();
	virtual void Update(double dt);

	virtual void Destroy();
};

#endif