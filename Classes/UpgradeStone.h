#ifndef UPGRADE_STONE_H
#define UPGRADE_STONE_H

class UpgradeStone
{
public:
	enum UPGRADE_TYPE
	{
		UT_FIRERATE = 0,
		UT_DAMAGE,
		UT_COUNT
	};

	static UpgradeStone* GenerateStone(int modifier);

	float modififyingValue = 0;
	float baseValue = 0;
	
private:

};

#endif