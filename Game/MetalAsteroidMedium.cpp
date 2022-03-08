#include "MetalAsteroidMedium.h"
#include "LifeInterface.h"
MetalAsteroidMedium::MetalAsteroidMedium(Vector3 initialPosition)
{
	realLocation = initialPosition;
}

MetalAsteroidMedium::~MetalAsteroidMedium()
{
}

void MetalAsteroidMedium::Construct()
{
	Super::Construct();
	AddComponent<Image>("XenonImages/MAster64.bmp", 8, 3, 2);
	AddComponent<Collider>();
}

void MetalAsteroidMedium::Start()
{
	Super::Start();
	SetTag("MetalAsteroidMedium");


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

	GetComponent<Collider>().SetVelocity(negativeVelocity);
}

void MetalAsteroidMedium::Update()
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
			Ilife->DecreaseLife(2);
			isDead = true;
			GetComponent<Collider>().asCollided = false;
		}
	}

	GetComponent<Transform>().position = GetComponent<Collider>().GetPosition();




}
