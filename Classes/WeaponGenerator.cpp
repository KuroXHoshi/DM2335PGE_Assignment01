#include "WeaponGenerator.h"

#include "cocos2d.h"
#include "Player.h"
#include "Shell.h"
#include "Swarmer.h"
#include "GameController.h"

using namespace cocos2d;

WeaponGenerator* WeaponGenerator::s_instance = nullptr;

WeaponGenerator * WeaponGenerator::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new WeaponGenerator();
	}
	return s_instance;
}

Weapon * WeaponGenerator::GetWeapon(WEAPON_TYPES type, int factionSide)
{
	Weapon* weapon = new Weapon();
	switch (type)
	{
	case WEAPON_TYPES::RIFLE:
		weapon->Set(17, 22, 1, 0, 1000, factionSide, "textures/Protagonist_Bullet.tga");
		break;
	case WEAPON_TYPES::SPOOLDOWN_RIFLE:
		weapon->Set(15, 30, 2, 0, 1000, factionSide, "textures/Protagonist_Bullet.tga");
		break;
	case WEAPON_TYPES::SHOTGUN:
		weapon->Set(85, 130, 1.5f, 1, 1500, factionSide, "textures/Protagonist_Bullet.tga");
		weapon->range = 250;
		break;
	case WEAPON_TYPES::FLAMETHROWER:
		weapon->Set(5, 10, 10, 2, 1000, factionSide, "textures/Protagonist_Bullet.tga");
		break;
	case WEAPON_TYPES::LENZ:
		weapon->Set(50, 100, 1.5f, 3, 1000, factionSide, "textures/Protagonist_Bullet.tga");
		break;
	case WEAPON_TYPES::SWARM_SUMMON:
		weapon->Set(50, 75, 2, 4, 750, factionSide, "textures/Protagonist_Bullet.tga");
		weapon->range = 5000;
		break;
	case WEAPON_TYPES::SUCTION_GUN:
		weapon->Set(100, 200, 10, 5, 750, factionSide, "textures/Protagonist_Bullet.tga");
		break;
	}
	return weapon;
}

Projectile * WeaponGenerator::GetProjectile(Weapon* weap)
{
	Projectile* proj = nullptr;
	int projectileType = weap->bulletType;
	bool gotCrit = false;
	int damage = weap->GetDamage(gotCrit);
	switch (projectileType)
	{
	case 1:
		//shotgun shell
	{
		ShotgunShell* ss = new ShotgunShell();
		ss->position = weap->position;
		ss->direction = weap->direction;
		ss->damage = damage;
		ss->speed = weap->bulletSpeed;
		ss->range = weap->GetRange();
		ss->factionTag = weap->factionTag;

		ss->critChance = weap->GetCritChance();
		ss->critDamage = weap->GetCritDamage();
		ss->bulletTexture = weap->bulletTexture;
		//ss->SetSpriteStuffs(weap->bulletTexture);

		proj = ss;
	}
		break;
	//case 2:
		//flame thrower
	//	break;
	case 3:
		//lenz
		break;
	case 4:
	{	//swarm army
		Swarmer * ss = new Swarmer();
		ss->position = weap->position;
		ss->direction = weap->direction;
		ss->damage = damage;
		ss->speed = weap->bulletSpeed;
		ss->range = weap->GetRange();
		ss->factionTag = weap->factionTag;

		ss->detectRange = ss->defaultDetectRange * weap->rangeMultiplier;
		if (weap->factionTag == 0)
			ss->parent = GameController::GetInstance()->player;

		proj = ss;
	}
		break;
	case 5:
		//suction
		break;
	default:
		proj = Projectile::Create(weap->position, weap->direction, damage, weap->bulletSpeed, weap->GetRange(), weap->factionTag);
		proj->isCrit = gotCrit;
		break;
	}

	std::string bulletTexture = weap->bulletTexture;
	proj->SetSpriteStuffs(bulletTexture);

	return proj;
}

