#pragma once

#include "SingletonTemplate.h"
#include "Weapon.h"

enum WEAPON_TYPES
{
	RIFLE,
	SPOOLDOWN_RIFLE, //slowly shoots slower
	SHOTGUN,

	FLAMETHROWER,
	LENZ,
	SWARM_SUMMON,
	SUCTION_GUN,
};


class WeaponGenerator : public Singleton <WeaponGenerator>
{
	static WeaponGenerator* s_instance;
public:
	WeaponGenerator* GetInstance();

	Weapon* GetRandomWeaponPickup();
};