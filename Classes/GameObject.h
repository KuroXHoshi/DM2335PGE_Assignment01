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
	virtual void Update(double dt) {};

	void SetSprite(std::string filename, std::string nodeName);
	void SetAnimFrames(Vector<SpriteFrame*> spriteFrameList, float delay);
};