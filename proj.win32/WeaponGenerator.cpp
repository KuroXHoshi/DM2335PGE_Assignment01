#include "WeaponGenerator.h"

#include "cocos2d.h"
#include "Player.h"

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

