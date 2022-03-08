#include "WeaponPowerUp.h"
#include "ShooterMissilesInterface.h"
#include <type_traits>




void WeaponPowerUp::Construct()
{
	Super::Construct();

	image = AddComponent<Image>("XenonImages/PUWeapon.bmp", 4 , 2, 4);
	AddComponent<Collider>();
	mySound = AddComponent<Sound>();
}

void WeaponPowerUp::Start()
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

void WeaponPowerUp::Update()
{
	Super::Update();

	GetComponent<Transform>().position = GetComponent<Collider>().GetPosition();


	if (GetComponent<Collider>().asCollided
		&& GetComponent<Collider>().GetCollisionResultObject() != nullptr)
	{
		ShooterMissilesInterface* shooter = nullptr;
		shooter = dynamic_cast<ShooterMissilesInterface*>(GetComponent<Collider>().GetCollisionResultObject());
		if (shooter != nullptr)
		{
			shooter->MissilePowerUp();
			GetComponent<Collider>().asCollided = false;
			mySound->PlaySound("SoundFiles/PowerUp.wav");
			Destroy(this);
		}
	}
}
 