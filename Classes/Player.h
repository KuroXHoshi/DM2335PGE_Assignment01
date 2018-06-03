#pragma once

#include "Character.h"
#include "GameObject.h"
#include "Controls.h"

class Player : public CharacterBase, public GameObject, public Controls
{
private:
	EventListenerKeyboard* kbListener;
	EventListenerMouse* mouseListener;
	//Controls controls;
public:
	Player();
	void Update(double dt);
	void Start();
	void LookAt(Vec2 target_);
	//void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event_);
	//void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event_);
	void onMousePressed(cocos2d::Event* event_);
	void onMouseReleased(cocos2d::Event* event_);
	void onMouseMove(cocos2d::Event* event_);
	EventListenerKeyboard* GetKbListener();
	EventListenerMouse* GetMouseListener();
};