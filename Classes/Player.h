#pragma once

#include "Character.h"
#include "GameObject.h"

class Player : public CharacterBase, public GameObject
{
public:
	Player();
	void Update(double dt);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event_);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event_);
	void onMousePressed(cocos2d::Event* event_);
	void onMouseReleased(cocos2d::Event* event_);
};