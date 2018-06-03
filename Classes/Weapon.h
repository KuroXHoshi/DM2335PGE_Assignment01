#ifndef WEAPON_H
#define WEAPON_H

#include "GameObject.h"

class Weapon : public GameObject
{
	bool isSet;
protected:
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
};

#endif // !WEAPON_H

