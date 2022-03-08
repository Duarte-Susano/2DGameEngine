#include "RockAsteroidSmall.h"
#include "Points.h"

RockAsteroidSmall::RockAsteroidSmall(Vector3 initialPosition, Vector3 Direction, Level* rhsMylevel, HUDScore* hudScore)
{
	realLocation = initialPosition;
	myLevel = rhsMylevel;
	AsteroidDirection = Direction;
	hud = hudScore;
}

RockAsteroidSmall::~RockAsteroidSmall()
{
	myLevel = nullptr;
}

void RockAsteroidSmall::Construct()
{
	Super::Construct();
	myImage = AddComponent<Image>("XenonImages/SAster32.bmp", 8, 2, 2);
	AddComponent<Collider>();
	mySound = AddComponent<Sound>();
}

void RockAsteroidSmall::Start()
{
	Super::Start();
	SetTag("RockAsteroidSmall");


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

	life = 1;
}

void RockAsteroidSmall::Update()
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
		Ilife->DecreaseLife(1);
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

void RockAsteroidSmall::DecreaseLife(int quantaty)
{
	LifeInterface::DecreaseLife(quantaty);

	myImage->color = { 100, 100, 100 };
	if (!isAlive)
	{
		mySound->PlaySound("SoundFiles/Explosion1.wav");
		myLevel->SpawnObject(new Points(GetComponent<Transform>().position, score));
		hud->AddScore(score);
		isDead = true;
	}
}
