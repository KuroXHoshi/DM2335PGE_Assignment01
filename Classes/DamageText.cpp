#include "DamageText.h"

#include "GameController.h"
#include "AndroidCompile.h"

void DamageText::Start()
{
	float fontsize = 16;
	if (isCrit)
		fontsize = 20;
	this->textLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", fontsize);
	GameController::GetInstance()->scene->addChild(this->textLabel, 1);

	textLabel->setAlignment(TextHAlignment::CENTER);

	textLabel->setString(to_string(this->damage));
	textLabel->setTextColor(Color4B(255, 255, 255, 255));
	if (isCrit)
	{
		textLabel->setTextColor(Color4B(255, 225, 0, 255));
	}
	textLabel->setPosition(this->position);
}

void DamageText::Update(double dt)
{
	this->et += dt;
	if (et >= duration)
	{
		this->Destroy();
		return;
	}

	float percentage = this->et / this->duration;

	this->position.y += this->speed * dt;
	textLabel->setPosition(this->position);
	if (isCrit == false)
	{
		textLabel->setTextColor(Color4B(255,255,255,255 * (1.0f - percentage)));
	}
	else {
		textLabel->setTextColor(Color4B(255, 225, 0, 255 * (1.0f - percentage)));
	}
}

void DamageText::Destroy()
{
	GameObject::Destroy();
	textLabel->removeFromParentAndCleanup(true);
}

DamageText * DamageText::Create(Vec2 & pos, int damage, bool isCrit)
{
	DamageText* dt = new DamageText();
	dt->position = pos;
	dt->damage = damage;
	dt->isCrit = isCrit;
	return nullptr;
}


