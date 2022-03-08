#include "MetalAsteroidSmall.h"
#include "LifeInterface.h"

MetalAsteroidSmall::MetalAsteroidSmall(Vector3 initialPosition)
{
	realLocation = initialPosition;
}

MetalAsteroidSmall::~MetalAsteroidSmall()
{
}

void MetalAsteroidSmall::Construct()
{
	Super::Construct();
	AddComponent<Image>("XenonImages/MAster32.bmp", 8, 2, 2);
	AddComponent<Collider>();
}

void MetalAsteroidSmall::Start()
{
	Super::Start();
	SetTag("MetalAsteroidSmall");


	GetComponent<Transform>().position = realLocation;

	GetComponent<Image>().PlayAnimation(idle);

	GetComponent<Collider>().MakeCollider(
		GetComponent<Transform>().position,
		GetComponent<Collider>().DynamicBody,
		GetComponent<Image>().imageWidth / 8,
		GetComponent<Image>().imageHeight / 2,
		0.0f,
		0.0f,
		0.0f,
		true,
		true);

	GetComponent<Collider>().SetVelocity(negativeVelocity);
}

void MetalAsteroidSmall::Update()
{

	Super::Update();

	if (GetComponent<Transform>().position.x < -80
		|| GetComponent<Transform>().position.y > 680
		|| GetComponent<Transform>().position.y < -80)
	{
		Destroy(this);
	}

	if (!isDead)
	{
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

	GetComponent<Transform>().position = GetComponent<Collider>().GetPosition();

}
