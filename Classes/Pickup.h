#pragma once

#include "GameObject.h"

class Pickup : public GameObject
{

public:
	GameObject* content;

	void PlayerPickUp();
};