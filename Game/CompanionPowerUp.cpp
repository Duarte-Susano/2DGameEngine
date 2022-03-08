#include "CompanionPowerUp.h"
#include "ShooterMissilesInterface.h"
#include <type_traits>
#include "Spaceship.h"
#include "ControllableCharacter.h"
#include "LifeInterface.h"

void CompanionPowerUp::Construct()
{
	Super::Construct();

	image = AddComponent<Image>("XenonImages/clone.bmp", 4, 5, 4);
	AddComponent<Collider>();
	mySound = AddComponent<Sound>();
}

void CompanionPowerUp::Start()
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

void CompanionPowerUp::Update()
{
	Super::Update();

	GetComponent<Transform>().position = GetComponent<Collider>().GetPosition();

	if (GetComponent<Collider>().asCollided
		&& GetComponent<Collider>().GetCollisionResultObject() != nullptr
		&& GetComponent<Collider>().GetCollisionResultObject()->GetTag() == "Spaceship")
	{
		mySound->PlaySound("SoundFiles/PowerUp.wav");
		Spaceship* spaceship = dynamic_cast<Spaceship*>(GetComponent<Collider>().GetCollisionResultObject());
		spaceship->SpawnCompanion();

		Destroy(this);
	}
}
