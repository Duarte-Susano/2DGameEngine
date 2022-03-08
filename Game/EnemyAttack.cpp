#include "EnemyAttack.h"
#include "LifeInterface.h"
EnemyAttack::~EnemyAttack()
{
	myLevel = nullptr;
}

void EnemyAttack::Construct()
{
	Super::Construct();
	AddComponent<Image>("XenonImages/EnWeap6.bmp", 8, 1, 3);
	AddComponent<Collider>();
}

void EnemyAttack::Start()
{
	Super::Start();
	SetTag("EnemyMissil");

	GetComponent<Transform>().position = myInitialPosition;

	GetComponent<Image>().PlayAnimation(idle);

	//Create Collider
	GetComponent<Collider>().MakeCollider(
		GetComponent<Transform>().position,
		GetComponent<Collider>().DynamicBody,
		3,
		3,
		myDirection.x * velocity,
		myDirection.y * velocity,
		0.0f,
		true,
		true);
}

void EnemyAttack::Update()
{
	Super::Update();


	GetComponent<Transform>().position = GetComponent<Collider>().GetPosition();

	if (GetComponent<Transform>().position.y < 0)
	{
		Destroy(this);
	}
	if (GetComponent<Transform>().position.y > 610)
	{
		Destroy(this);
	}
	if (GetComponent<Transform>().position.x < 0)
	{
		Destroy(this);
	}
	if (GetComponent<Transform>().position.x > 900)
	{
		Destroy(this);
	}



	if (GetComponent<Collider>().asCollided
		&& GetComponent<Collider>().GetCollisionResultObject() != nullptr
		&& (GetComponent<Collider>().GetCollisionResultObject()->GetTag() == "Spaceship"
		|| GetComponent<Collider>().GetCollisionResultObject()->GetTag() == "Companion"))

	{
		LifeInterface* Ilife = dynamic_cast<LifeInterface*>(GetComponent<Collider>().GetCollisionResultObject());
		Ilife->DecreaseLife(1);
		GetComponent<Collider>().asCollided = false;
		Destroy(this);
	}


	if (GetComponent<Collider>().asCollided
		&& GetComponent<Collider>().GetCollisionResultObject() != nullptr
		&& GetComponent<Collider>().GetCollisionResultObject()->GetTag() == "Missile")

	{
		Destroy(this);
	}

}
