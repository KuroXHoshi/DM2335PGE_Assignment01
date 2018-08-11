#ifndef GRAVITY_BULLET_H
#define GRAVITY_BULLET_H

#include "Projectile.h"

class GravityBullet : public Projectile
{
public:
	const float defaultExplosionRange = 250.0f;
	float explosionRange = defaultExplosionRange;

	Vec2 target;

	const float defaultDetectRange = 200.0f;
	float detectRange = defaultDetectRange;

	float turnAngleSpd = 180.0f;

	int state = 0; // 0 flying straight detecting nearby units, 1 fly towards target

	std::string vortexTexture;

	virtual void Update(double dt);
	virtual void Start();

	virtual void Destroy();

	void FlyStraight(double dt);
	void GoThereExplode(double dt);

};

#endif