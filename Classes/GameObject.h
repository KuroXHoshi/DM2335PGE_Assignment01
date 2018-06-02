#pragma once

#include "cocos2d.h"

using namespace cocos2d;

//all these values have to be in bit form / power of 2
//physics use this bit method to differentiate the layers, something like in unity
//When two collide, their categorymask is tested against contacttestmask by perfoming &&
//if either results in NON-ZERO , collidebegin is started

//so, as long as categorybitmask and contacttestbitmask have something same, it works
enum BITMASK_ENUM
{
	BITMASK_PLAYER = 0b00001,
	BITMASK_PLAYER_BULLET = 0b0010,
	BITMASK_ENEMY = 0b0100,
	BITMASK_ENEMY_BULLET = 0b1000,

	//LAST
	BITMASK_EVERYTHING = 0xFFFFFFFF
};

enum TAGENUM
{
	PLAYER = 0,
	BULLET,
	ENEMY
};

class GameObject
{
	//deletion Flag. if true, deletes gameobject at the end of the frame update
	bool isDone;
public:
	//unique ID for gameobjects
	int id;

	//position
	cocos2d::Vec2 position;

	//direciton
	cocos2d::Vec2 direction;

	//scale
	cocos2d::Vec2 scale;

	//active flag
	bool active;

	//sprite renderable
	cocos2d::Node* spriteNode;
	cocos2d::Sprite* sprite;

	cocos2d::Animate* animate;

	//the physics body
	cocos2d::PhysicsBody* physicsBody;
	EventListenerPhysicsContact* contactListener;

	//ID counter
	static int idCounter;

	//tag
	TAGENUM tag;

	cocos2d::Vector<SpriteFrame*> animFrames;

public:
	GameObject();
	~GameObject();
	virtual void Update(double dt) {};

	void SetSprite(std::string filename, std::string nodeName);
	void SetAnimFrames(Vector<SpriteFrame*> spriteFrameList, float delay);
	void SetPhysics(bool isDynamic, cocos2d::Vec2 velocity, bool isGravityEnabled);

	virtual bool OnContactBegin(cocos2d::PhysicsContact& contact);

	//Destroys the gameobject at the end of the update frame
	void Destroy();

	//Returns true if this gameobject is going to be destroyed at the end of update frame
	//useful for things like projectile, check if projectile is dead to avoid/checks for collision response
	bool isDead();

};

