#include "MetalAsteroidBig.h"
#include "LifeInterface.h"
MetalAsteroidBig::MetalAsteroidBig(Vector3 initialPosition)
{
	realLocation = initialPosition;
}

MetalAsteroidBig::~MetalAsteroidBig()
{
}

void MetalAsteroidBig::Construct()
{
	Super::Construct();
	AddComponent<Image>("XenonImages/MAster96.bmp", 5, 5, 2);
	AddComponent<Collider>();
}

void MetalAsteroidBig::Start()
{
	Super::Start();
	SetTag("MetalAsteroidBig");


	GetComponent<Transform>().position = realLocation;

	GetComponent<Image>().PlayAnimation(idle);

	GetComponent<Collider>().MakeCollider(
		GetComponent<Transform>().position,
		GetComponent<Collider>().DynamicBody,
		GetComponent<Image>().imageWidth / 5,
		GetComponent<Image>().imageHeight / 5,
		0.0f,
		0.0f,
		0.0f,
		true,
		true);

	GetComponent<Collider>().SetVelocity(negativeVelocity);
}

void MetalAsteroidBig::Update()
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
			Ilife->DecreaseLife(3);
			isDead = true;
			GetComponent<Collider>().asCollided = false;
		}
	}

	GetComponent<Transform>().position = GetComponent<Collider>().GetPosition();



	
}
