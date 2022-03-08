#include "RusherEnemy.h"
#include "Points.h"

RusherEnemy::RusherEnemy(Vector3 initialPosition, Level* rhsMylevel, HUDScore* hudScore)
{
	realLocation = initialPosition;
	myLevel = rhsMylevel;
	hud = hudScore;
}

RusherEnemy::~RusherEnemy()
{
}

void RusherEnemy::Construct()
{
	Super::Construct();
	myImage = AddComponent<Image>("XenonImages/Rusher.bmp", 4, 6 ,2);
	AddComponent<Collider>();
	mySound = AddComponent<Sound>();
}

void RusherEnemy::Start()
{
	Super::Start();
	SetTag("Enemy");

	GetComponent<Transform>().position = realLocation;

	GetComponent<Image>().PlayAnimation(idle);

	GetComponent<Collider>().MakeCollider(
		GetComponent<Transform>().position,
		GetComponent<Collider>().DynamicBody,
		GetComponent<Image>().imageWidth/ 4,
		GetComponent<Image>().imageHeight / 6,
		0.0f,
		0.0f,
		0.0f,
		true,
		true);

	GetComponent<Collider>().SetVelocity(positiveVelocity);

	life = 5;
}

void RusherEnemy::Update()
{
Super::Update();

	if (myImage->color.x > 10)
	{
		--damageTimer;
	}

	if (damageTimer <= 0)
	{
		myImage->color = {1,1,1};
		damageTimer = 100;
	}

	if (isDead)
	{
		Destroy(this);
	}

	if (GetComponent<Transform>().position.x <= 0)
	{
		GetComponent<Collider>().SetVelocity(positiveVelocity);
	}
	if (GetComponent<Transform>().position.x >= 900)
	{
		GetComponent<Collider>().SetVelocity(negativeVelocity);
	}


	GetComponent<Transform>().position = GetComponent<Collider>().GetPosition();

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
}

void RusherEnemy::DecreaseLife(int quantaty)
{
	LifeInterface::DecreaseLife(quantaty);

	myImage->color = {100, 100, 100};

	if (!isAlive)
	{
		mySound->PlaySound("SoundFiles/Explosion1.wav");
		myLevel->SpawnObject(new Points(GetComponent<Transform>().position, score));
		hud->AddScore(100);
		isDead = true;
	}
}
