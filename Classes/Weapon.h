#ifndef WEAPON_H
#define WEAPON_H

#include "GameObject.h"
#include "UpgradeStone.h"
#include "Projectile.h"

class Weapon : public GameObject
{
	bool isSet;
public:
	int min_damage;
	int max_damage;

	int bulletType;
	float bulletSpeed;
	int factionTag; //which side this belongs to

	//i think this is for buffs. ignore for now
	bool fast;
	bool buff;
	float fastTimer;
	float buffTimer;

	//Default dmg values before buffs
	int defaultMinDmg;
	int defaultMaxDmg;

	//Attack speed
	double attackspeed_timer;
	double attackspeed_triggerTime;

	//Rands damage between min and max
	int GetDamage();

	//bullet sprite image to be rendered
	std::string bulletTexture;
public:
	std::string name;

	Weapon();
	virtual ~Weapon();
	virtual void Update(double dt);

	//Call this function to Shoot weapon
	virtual void Discharge();

	//Call this function to initialize the weapon
	virtual void Set(int min_dmg, int max_dmg, double attacks_per_sec, int bulletType, float bulletSpeed, int factionSide, std::string bulletsrite = "Blue_Front1.png");

	//Upgrade stones
	std::vector<UpgradeStone*> modifiers;
	void AddStone(UpgradeStone* stone);

	float GetAttackSpeed();
	
	class MultiShotInfo
	{
	public:
		float elasped = 0.0f;
		float triggerTime = 0.1f;
		Projectile* proj;
	};
	std::vector<MultiShotInfo*> multishotVec;

	float damageMultiplier = 1.0f;

	float baseCritChance = 0.0f;
	float baseCritDamage = 1.5f;
	float critChanceMultiplier = 1.0f;
	float critDamageMultiplier = 1.0f;
	float GetCritChance() { return baseCritChance * critChanceMultiplier; }
	float GetCritDamage() { return baseCritDamage * critDamageMultiplier; }
	int GetDamage(bool& isCrit) { 
		int mindmg = min_damage * damageMultiplier;
		int maxdmg = max_damage * damageMultiplier;
		return this->min_damage + (rand() % (this->max_damage - this->min_damage));
	}

	float range = 1000.0f;
	float rangeMultiplier = 1.0f;
	float GetRange() { return (range * rangeMultiplier); }

	float attackSpeedMultiplier = 1.0f;
	
};

#endif // !WEAPON_H

