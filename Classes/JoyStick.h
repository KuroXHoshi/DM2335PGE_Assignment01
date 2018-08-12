#pragma once
#include "cocos2d.h"
#include "GameObject.h"
#include "Player.h"

class JoyStick
{
public:

	~JoyStick();

	void init(cocos2d::Layer* layer);
	void update(float dt_);
	cocos2d::Layer* hudLayer;
	static JoyStick* s_instance;
	Node* joystick_bg_left;
	Node* joystick_bg_right;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	Player* player;

	void AttachPlayer(Player*);
	static JoyStick* GetInstance();

	virtual bool onTouchesBegan(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event*);
	virtual void onTouchesEnded(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event*);
	virtual void onTouchesMoved(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event*);
	virtual void onTouchesCancelled(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event*);

	Vec2 GetTouchLocation(Vec2 touchLocation_);

	EventListenerTouchAllAtOnce* GetEventListenerTouch();
private:
	JoyStick();
	EventListenerTouchAllAtOnce* eventListenerTouch;
	bool leftJoyHeld;
	bool rightJoyHeld;
	int leftTouch;
	int rightTouch;
	Vec2 leftJoyDirection;
	Vec2 rightJoyDirection;
};

