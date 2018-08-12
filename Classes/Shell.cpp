#include "Shell.h"

void ShotgunShell::Start()
{
	//split shells
	this->Destroy();

	float halfAngle = spreadAngle * 0.5f;

	int pelletdmg = (int)((float)this->damage / (float)numOfPellets);
	for (int i = 0; i < numOfPellets; ++i)
	{
		float randAngle = -halfAngle + rand() % (int)spreadAngle;
		Vec2 pelletDir = direction;
		pelletDir = pelletDir.rotateByAngle(Vec2(0, 0), randAngle * 3.14159265f / 180.0f);
		
		bool isCrit = (rand() % 100) <= (critChance * 100);
		int finalDmg = (isCrit ? pelletdmg * critDamage : pelletdmg);

		Projectile* pellet = new Projectile();
		pellet->position = this->position;
		pellet->direction = pelletDir;
		pellet->damage = finalDmg;
		pellet->speed = this->speed;
		pellet->range = this->range;
		pellet->factionTag = this->factionTag;
		pellet->SetSpriteStuffs(bulletTexture);

		//DBOUT(i << " dir: " << pelletDir.x << " " << pelletDir.y);
	}
}

void ShotgunShell::Update(double dt)
{
	Projectile::Update(dt);
}
