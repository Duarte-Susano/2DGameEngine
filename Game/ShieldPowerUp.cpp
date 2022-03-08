#include "ShieldPowerUp.h"
#include <type_traits>
#include "LifeInterface.h"
#include "Spaceship.h"

void ShieldPowerUp::Construct()
{
	Super::Construct();

	image = AddComponent<Image>("XenonImages/PUShield.bmp", 4, 2, 4);
	AddComponent<Collider>();
	mySound = AddComponent<Sound>();
}

void ShieldPowerUp::Start()
{
	Super::Start();

	GetComponent<Transform>().position = initialPosition;
	image->PlayAnimation(animation);

	GetComponent<Collider>().MakeCollider(
		GetComponent<Transform>().position,
		GetComponent<Collider>().DynamicBody,
		(image->imageWidth / image->nColumns),
		(image->imageHeight / image->nRows),
		-12.0f,
		0.0f,
		0.0f,
		false,
		false);

	myTag = "PowerUp";

}

void ShieldPowerUp::Update()
{
	Super::Update();


	GetComponent<Transform>().position = GetComponent<Collider>().GetPosition();

	if (GetComponent<Collider>().asCollided
		&& GetComponent<Collider>().GetCollisionResultObject() != nullptr)
	{

		if (GetComponent<Collider>().GetCollisionResultObject()->GetTag() == "Spaceship")
		{
			mySound->PlaySound("SoundFiles/PowerUp.wav");
			Spaceship* spaceship = static_cast<Spaceship*>(GetComponent<Collider>().GetCollisionResultObject());
			spaceship->AddGameLifes(1);
			Destroy(this);
		}

		if (GetComponent<Collider>().GetCollisionResultObject()->GetTag() == "Companion")
		{
			mySound->PlaySound("SoundFiles/PowerUp.wav");
			LifeInterface* life = dynamic_cast<LifeInterface*>(GetComponent<Collider>().GetCollisionResultObject());
			life->IncreaseLife(5);
			Destroy(this);
		}
	}
}
