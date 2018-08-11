#ifndef SWARMER_H
#define SWARMER_H

#include "Projectile.h"

class Swarmer : public Projectile
{
public:
	GameObject* parent = nullptr;
	bool antiClockwise = true;
	float initialRad = 0.0f;

	const float defaultDetectRange = 300.0f;
	float detectRange = defaultDetectRange;
	Vec2 target;

	int state = 0; //0 move to circumference, 1 rotate around circumference, 2 chase target

	virtual void Update(double dt);
	virtual void Start();

	void SetStartRadian(Vec2 dir);

	void MoveToCircumference(double dt);
	void RotateAround(double dt);
	void ChaseTarget(double dt);
};

#endif