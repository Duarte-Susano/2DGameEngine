#include "RockAsteroidMedium.h"
#include "Points.h"
#include "RockAsteroidSmall.h"

RockAsteroidMedium::RockAsteroidMedium(Vector3 initialPosition, Vector3 Direction, Level* rhsMylevel, HUDScore* hudScore)
{
	realLocation = initialPosition;
	myLevel = rhsMylevel;
	AsteroidDirection = Direction;
	hud = hudScore;
}

RockAsteroidMedium::~RockAsteroidMedium()
{
}

void RockAsteroidMedium::Construct()
{
	Super::Construct();
	myImage = AddComponent<Image>("XenonImages/SAster64.bmp", 8, 3, 2);
	AddComponent<Collider>();
	mySound = AddComponent<Sound>();
}

void RockAsteroidMedium::Start()
{
	Super::Start();
	SetTag("RockAsteroidMedium");


	GetComponent<Transform>().position = realLocation;

	GetComponent<Image>().PlayAnimation(idle);

	GetComponent<Collider>().MakeCollider(
		GetComponent<Transform>().position,
		GetComponent<Collider>().DynamicBody,
		GetComponent<Image>().imageWidth / 8,
		GetComponent<Image>().imageHeight / 3,
		0.0f,
		0.0f,
		0.0f,
		true,
		true);

	GetComponent<Collider>().SetVelocity(AsteroidDirection);

	life = 3;


}

void RockAsteroidMedium::Update()
{
	Super::Update();

	if (isDead)
	{
		Destroy(this);
	}

	GetComponent<Transform>().position = GetComponent<Collider>().GetPosition();

	if (GetComponent<Transform>().position.x < -80
		|| GetComponent<Transform>().position.y > 680
		|| GetComponent<Transform>().position.y < -80)
	{
		Destroy(this);
	}

	//Adding the movement to the transform

	if (GetComponent<Collider>().asCollided
		&& GetComponent<Collider>().GetCollisionResultObject() != nullptr
		&& (GetComponent<Collider>().GetCollisionResultObject()->GetTag() == "Spaceship"
			|| GetComponent<Collider>().GetCollisionResultObject()->GetTag() == "Companion"))
	{
		LifeInterface* Ilife = dynamic_cast<LifeInterface*>(GetComponent<Collider>().GetCollisionResultObject());
		Ilife->DecreaseLife(2);
		isDead = true;
		GetComponent<Collider>().asCollided = false;
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

void RockAsteroidMedium::DecreaseLife(int quantaty)
{
	LifeInterface::DecreaseLife(quantaty);

	myImage->color = { 100, 100, 100 };

	if (!isAlive)
	{
		mySound->PlaySound("SoundFiles/Explosion1.wav");
		myLevel->SpawnObject(new Points(GetComponent<Transform>().position, score));
		hud->AddScore(score);
		
		Vector3 asteroid1 = { AsteroidDirection.x , 5.0f ,0.0f };
		Vector3 asteroid2 = { AsteroidDirection.x , -5.0f ,0.0f };

		myLevel->SpawnObject(new RockAsteroidSmall(GetComponent<Transform>().position, asteroid1, myLevel, hud));
		myLevel->SpawnObject(new RockAsteroidSmall(GetComponent<Transform>().position, asteroid2, myLevel, hud));

		isDead = true;
	}
}
