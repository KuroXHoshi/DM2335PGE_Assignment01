#pragma once

class CharacterBase
{
public:
	int hitpoint;
	int faction;
	virtual ~CharacterBase() {}
protected:
	CharacterBase() : hitpoint(0), faction(0) {}
};
