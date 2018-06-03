#pragma once

#include "Character.h"
#include "GameObject.h"
#include "Controls.h"

class Player : public CharacterBase, public GameObject, public Controls
{
private:
	EventListenerKeyboard* kbListener;
	//Controls controls;
public:
	Player();
	void Update(double dt);
	//void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event_);
	//void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event_);
	void onMousePressed(cocos2d::Event* event_);
	void onMouseReleased(cocos2d::Event* event_);
	EventListenerKeyboard* GetKbListener();
};