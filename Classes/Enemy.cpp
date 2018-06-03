#include "Enemy.h"

Enemy::Enemy() : player(nullptr), factionTag(TAGENUM::ENEMY), health(1), damage(1), speed(10.f)
{

}

Enemy::~Enemy()
{

}

void Enemy::Start()
{

}

void Enemy::Update(double dt)
{
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
