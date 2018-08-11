#include "Flame.h"

#include "MyMath.h"

void Flame::Start()
{
	//float rad = inaccuracyDegCone * PI / 180.0f;
	float halfDeg = inaccuracyDegCone * 0.5f;

	float rotation = -halfDeg + (float)(rand() / (float)(RAND_MAX / (inaccuracyDegCone)));
	float rotationRad = rotation * PI / 180.0f;
	this->direction = this->direction.rotateByAngle(Vec2(0, 0), rotationRad);

	physicsBody->setVelocity(this->direction * speed);
}

void Flame::Update(double dt)
{
	this->position = physicsBody->getPosition();
	
	distTravelled += speed * dt;
	if (distTravelled > range)
		this->isDone = true;
}

void Flame::Destroy()
{
}
