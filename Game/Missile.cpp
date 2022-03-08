#include "Missile.h"
#include "LifeInterface.h"

Missile::Missile(Vector3 initialPosition, Tier rhsTier)
{
	myInitialPosition = initialPosition;
	myTier = rhsTier;
}

Missile::~Missile()
{
}

void Missile::Construct()
{
	Super::Construct();
	//Adds an Image
	AddComponent<Image>("XenonImages/missile.bmp", 2, 3, 1);
	AddComponent<Collider>();
}

void Missile::Start()
{
	Super::Start();

	//Set tag
	SetTag("Missile");

	//Set the initial position to the transform
	GetComponent<Transform>().position = myInitialPosition;
	GetComponent<Transform>().rotation.z = -90;


	switch (myTier)
	{
	case Missile::light:
		GetComponent<Image>().PlayAnimation(lightAnim);
		damage = 1;
		break;
	case Missile::medium:
		GetComponent<Image>().PlayAnimation(mediumAnim);
		damage = 2;
		break;
	case Missile::heavy:
		GetComponent<Image>().PlayAnimation(heavyAnim);
		damage = 4;
		break;
	default:
		break;
	}



	//Create Collider
	GetComponent<Collider>().MakeCollider(
	GetComponent<Transform>().position,
	GetComponent<Collider>().DynamicBody,
	2,
	2,
	velocity,
	0.0f,
	0.0f,
	true,
	true);
}

void Missile::Update()
{
	Super::Update();
	//moves the missile up;

	GetComponent<Transform>().position = GetComponent<Collider>().GetPosition();

	//As Collided
	if (GetComponent<Collider>().asCollided
		&& GetComponent<Collider>().GetCollisionResultObject() != nullptr
		&& GetComponent<Collider>().GetCollisionResultObject()->GetTag() != "Spaceship"
		&& GetComponent<Collider>().GetCollisionResultObject()->GetTag() != "PowerUp"
		&& GetComponent<Collider>().GetCollisionResultObject()->GetTag() != "Missile"
		&& GetComponent<Collider>().GetCollisionResultObject()->GetTag() != "Companion")
	{
		LifeInterface* Ilife = dynamic_cast<LifeInterface*>(GetComponent<Collider>().GetCollisionResultObject());
		if (Ilife != nullptr)
		{
			Ilife->DecreaseLife(damage);
		}
		GetComponent<Collider>().asCollided = false;
		GetComponent<Image>().PlayAnimation(explosion);
		GetComponent<Collider>().SetVelocity(Vector3(0, 0, 0));
		GetComponent<Collider>().DisableCollider();
		hasExploded = true;
	}

	if (hasExploded && GetComponent<Image>().EndOfAnimation())
	{
		Destroy(this);
	}


	if (GetComponent<Transform>().position.x > 900)
	{
		Destroy(this);
	}
	
}

void Missile::FixUpdate()
{
	Super::FixUpdate();

	if (!pendingDestroy)
	{
		
	}
}
