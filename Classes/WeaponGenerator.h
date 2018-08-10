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
	static WeaponGenerator* GetInstance();

	//side : 0 = player, 1 = enemy
	Weapon* GetWeapon(WEAPON_TYPES type, int factionSide);
	Projectile* GetProjectile(Weapon* weap);
};