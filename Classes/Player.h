#pragma once

#include "Character.h"
#include "GameObject.h"
#include "Controls.h"
#include "Weapon.h"
#include "SimpleAudioEngine.h"
#include "UpgradeStone.h"

class Player : public CharacterBase, public GameObject, public Controls
{
private:
	EventListenerKeyboard* kbListener;
	EventListenerMouse* mouseListener;
	//Controls controls;
	Weapon* weapon;
	TAGENUM factionTag;
	int health;
	CocosDenshion::SimpleAudioEngine *audio;
	
public:
	Player();
	void Update(double dt);
	void Start();
	void LookAt(Vec2 target_);
	inline int GetHealth() { return health; }
	inline void SetHealth(int _hp) { health = _hp; }
	//void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event_);
	//void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event_);
	void onMousePressed(cocos2d::Event* event_);
	void onMouseReleased(cocos2d::Event* event_);
	void onMouseMove(cocos2d::Event* event_);
	EventListenerKeyboard* GetKbListener();
	EventListenerMouse* GetMouseListener();
	void FireWeapon(Vec2 target_);

	//Upgrade Stones to affect the multipliers on equiped weaps
	const int stoneModifierSize = 6;
	UpgradeStone* stoneModifiers[6] = { nullptr, };
};