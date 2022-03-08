#include "DroneEnemy.h"
#include "Points.h"

DroneEnemy::DroneEnemy(Vector3 initialPosition, Level* rhsMylevel, HUDScore* hudScore)
{
	realLocation = initialPosition;
	myLevel = rhsMylevel;
	hud = hudScore;
	heigth = initialPosition.y;
}

DroneEnemy::~DroneEnemy()
{
	myLevel = nullptr;
}

void DroneEnemy::Construct()
{
	Super::Construct();
	myImage = AddComponent<Image>("XenonImages/drone.bmp", 8, 2, 2);
	AddComponent<Collider>();
	mySound = AddComponent<Sound>();
}

void DroneEnemy::Start()
{
	Super::Start();
	SetTag("Drone");


	GetComponent<Transform>().position = realLocation;

	GetComponent<Image>().PlayAnimation(idle);

	GetComponent<Collider>().MakeCollider(
		GetComponent<Transform>().position,
		GetComponent<Collider>().DynamicBody,
		myImage->imageWidth / myImage->nColumns,
		myImage->imageHeight / myImage->nRows,
		0.0f,
		0.0f,
		0.0f,
		true,
		true);

	life = 2;


}

void DroneEnemy::Update()
{
	Super::Update();

	if (isDead)
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

	time += 0.005f;

	y = fabs(cos(time) * 35 + heigth);


	Vector3 finalPos;
	finalPos = {GetComponent<Transform>().position.x + velocity, y, 0.0f};
	

	if (GetComponent<Transform>().position.x <= 00)
	{
		velocity = positiveVelocity;
	}
	if (GetComponent<Transform>().position.x >= 900)
	{
		velocity = negativeVelocity;
	}



	Vector3 fVel = finalPos - GetComponent<Collider>().GetPosition();


	GetComponent<Collider>().SetVelocity(fVel);
	GetComponent<Transform>().position = GetComponent<Collider>().GetPosition();

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
		mySound->PlaySound("SoundFiles/Explosion1.wav");
	}
}

void DroneEnemy::DecreaseLife(int quantaty)
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