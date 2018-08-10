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
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	Player* player;

	void AttachPlayer(Player*);
	static JoyStick* GetInstance();

	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);

	EventListenerTouchOneByOne* GetEventListenerTouch();
private:
	JoyStick();
	EventListenerTouchOneByOne* eventListenerTouch;
	bool leftJoyHeld;
	int leftTouch;
	int rightTouch;
	Vec2 leftJoyDirection;
};

