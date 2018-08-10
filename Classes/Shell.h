#pragma once

#include "Projectile.h"

class ShotgunShell : public Projectile
{
public:
	float spreadAngle = 30.0f;
	int numOfPellets = 10;
	float critChance = 0.0f;
	float critDamage = 1.5f;

	std::string bulletTexture = "";

	virtual void Update(double dt);
	virtual void Start();
};