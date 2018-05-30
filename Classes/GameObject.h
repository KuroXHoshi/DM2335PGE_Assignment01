#pragma once

#include "cocos2d.h"

using namespace cocos2d;

enum TAGENUM
{
	PLAYER,
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

	//Destroys the gameobject at the end of the update frame
	void Destroy();

	//Returns true if this gameobject is going to be destroyed at the end of update frame
	//useful for things like projectile, check if projectile is dead to avoid/checks for collision response
	bool isDead();
};