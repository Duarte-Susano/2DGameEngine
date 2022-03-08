#include "Companion.h"

void Companion::Construct()
{
	Super::Construct();

	myImage = AddComponent<Image>("XenonImages/clone.bmp", 4, 5, 4);
	AddComponent<Collider>();
	mySound = AddComponent<Sound>();
}

void Companion::Start()
{
	Super::Start();

	SetTag("Companion");

	myImage->PlayAnimation(Idle);
	GetComponent<Transform>().rotation.z = -90;


	if (leftCompanion)
	{
		GetComponent<Transform>().position = mySpaceship->GetComponent<Transform>().position; - yOffSet;
	}
	else
	{
		GetComponent<Transform>().position = mySpaceship->GetComponent<Transform>().position; + yOffSet;
	}
	GetComponent<Transform>().position = mySpaceship->GetComponent<Transform>().position;

	//Create Collider
	GetComponent<Collider>().MakeCollider(
		GetComponent<Transform>().position,
		GetComponent<Collider>().DynamicBody,
		(myImage->imageWidth / myImage->nColumns),
		(myImage->imageHeight / myImage->nRows),
		0.0f,
		0.0f,
		0.0f,
		true,
		true);

	life = 5;
	maxLife = 5;
}

void Companion::Update()
{
	Super::Update();

	//Set Position
	Vector3 newPosition = mySpaceship->GetComponent<Transform>().position;

	if (xOffSet < -50)
	{
		velocity *= -1;
	}
	if (xOffSet > 40)
	{
		velocity *= -1;
	}

	xOffSet += velocity;



	if (leftCompanion)
	{
		newPosition.y -= yOffSet;
	}
	else
	{
		newPosition.y += yOffSet;
	}

	newPosition.x += xOffSet;

	float finalX = newPosition.x - GetComponent<Transform>().position.x;
	float finalY = newPosition.y - GetComponent<Transform>().position.y;

	Vector3 finalVelocity = {finalX, finalY, 0.0f};

	GetComponent<Collider>().SetVelocity(finalVelocity);

	GetComponent<Transform>().position = GetComponent<Collider>().GetPosition();

	//Shoot
	shootTime += 0.1f;

	if (shootTime > timeToShoot)
	{
		mySound->PlaySound("SoundFiles/Gun1.wav");
		SpawnMissile(GetComponent<Transform>().position, myLevel);

		shootTime = 0;
	}


	if (die && GetComponent<Image>().EndOfAnimation())
	{
		Destroy(this);
	}

	if (myImage->color.x > 10)
	{
		--damageTimer;
	}

	if (damageTimer <= 0)
	{
		myImage->color = { 1,1,1 };
		damageTimer = 100;
	}

}

void Companion::DecreaseLife(int quantaty)
{
	LifeInterface::DecreaseLife(quantaty);

	myImage->color = { 100, 100, 100 };

	if (!isAlive)
	{
		if (leftCompanion)
		{
			mySpaceship->companionLeft = false;
		}
		else
		{
			mySpaceship->companionRight = false;
		}
		mySound->PlaySound("SoundFiles/Explosion1.wav");
		die = true;
		GetComponent<Image>().PlayAnimation(Dead);
		GetComponent<Collider>().SetVelocity(Vector3(0, 0, 0));
		GetComponent<Collider>().DisableCollider();
	}
}
