#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "cocos2d.h"
#include "Player.h"

class UserInterface
{
private:
	UserInterface() {}
	~UserInterface() {}

	static UserInterface* instance;
	Player* player;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Layer* hudLayer;
	Node* HealthBar;
	cocos2d::Sprite* HealthBarSprite;
	float MaxScale;
	float MaxPlayerHP;

public:
	static UserInterface* GetInstance();

	void init(cocos2d::Layer* layer);
	void update(float dt_);
	void AttachPlayer(Player* _input);

};

#endif