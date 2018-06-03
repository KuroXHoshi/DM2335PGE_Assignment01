#include "Enemy.h"

Enemy::Enemy() : LastPlayerPosition(0, 0), factionTag(TAGENUM::ENEMY), health(1), damage(1), speed(10.f)
{

}

Enemy::~Enemy()
{

}

void Enemy::Start()
{
	VisibleSize = Director::getInstance()->getVisibleSize();
}

void Enemy::Update(double dt)
{
	// Return if not active
	if (!active)
		return;
	
	// Set not active when off screen
	/*if (position.x < -50 || position.x > VisibleSize.width + 50 ||
		position.y < -50 || position.y > VisibleSize.height + 50)
	{
		active = false;
	}*/
}

Enemy * Enemy::Create(cocos2d::Vec2 pos, cocos2d::Vec2 playerPos, int damage, float speed, int factionTag)
{
	Enemy* enemy = new Enemy();
	enemy->LastPlayerPosition = playerPos;
	enemy->factionTag = (TAGENUM)factionTag;
	enemy->position = pos;
	enemy->damage = damage;
	enemy->speed = speed;

	return enemy;
}
