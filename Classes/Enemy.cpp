#include "Enemy.h"

Enemy::Enemy() : player(nullptr), factionTag(TAGENUM::ENEMY), health(1), damage(1), speed(10.f)
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
	Vec2 dir = player->sprite->getPosition() - sprite->getPosition();
	dir.normalize();
	physicsBody->setVelocity(dir * speed);
}

Enemy * Enemy::Create(cocos2d::Vec2 pos, Player* player, int damage, float speed, int factionTag)
{
	Enemy* enemy = new Enemy();
	enemy->player = player;
	enemy->factionTag = (TAGENUM)factionTag;
	enemy->position = pos;
	enemy->damage = damage;
	enemy->speed = speed;

	return enemy;
}
