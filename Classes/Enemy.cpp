#include "Enemy.h"
#include "Functions.h"

Enemy::Enemy() : player(nullptr), factionTag(TAGENUM::ENEMY), health(1), damage(1), speed(10.f)
{

}

//Enemy::~Enemy()
//{
//
//}

void Enemy::Start()
{
	//VisibleSize = Director::getInstance()->getVisibleSize();
}

void Enemy::Update(double dt)
{
	Vec2 dir = player->sprite->getPosition() - sprite->getPosition();
	dir.normalize();
	physicsBody->setVelocity(dir * speed);
	sprite->setRotation(-90 + atan2(dir.x, dir.y) * 180 / 3.14159265f);
	healthLabel->setString(std::to_string(health));
	healthLabel->setPosition(sprite->getPosition().x, sprite->getPosition().y - 50);
}

Enemy * Enemy::Create(cocos2d::Vec2 pos, Player* player, int health, int damage, float speed, int factionTag)
{
	Enemy* enemy = new Enemy();
	enemy->player = player;
	enemy->factionTag = (TAGENUM)factionTag;
	enemy->health = health;
	enemy->position = pos;
	enemy->damage = damage;
	enemy->speed = speed;

	return enemy;
}